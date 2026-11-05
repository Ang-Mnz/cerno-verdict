
#include "camera_controller.hpp"

#include <unistd.h>
#include <sys/wait.h>
#include <poll.h>
#include <signal.h>

#include <cerrno>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

CameraController::CameraController(
    const std::string& python_path,
    const std::string& script_path
)
    : python_path_(python_path),
      script_path_(script_path)
{
}

CameraController::~CameraController()
{
    stop();
}

bool CameraController::start()
{
	// Identifiant processus puthon
    if (process_id_ > 0)
    {
        return true;
    }

    // Création des pipes de communication
    if (pipe(input_pipe_) == -1)
    {
        std::cerr << "Erreur lors de la création du pipe d'entrée\n";
        return false;
    }

    if (pipe(output_pipe_) == -1)
    {
        std::cerr << "Erreur lors de la création du pipe de sortie\n";

        close(input_pipe_[0]);
        close(input_pipe_[1]);

        input_pipe_[0] = -1;
        input_pipe_[1] = -1;

        return false;
    }

	// Nouveau processus
    process_id_ = fork();

    if (process_id_ == -1)
    {
        std::cerr << "Erreur lors de la création du processus Python\n";
        stop();
        return false;
    }

    // Processus enfant : s'occupe de Python
    if (process_id_ == 0)
    {
		// Création de copies de sorties et entrées standard
		// Remplacer l'entrée standard par l'extremité de lecture de notre pipe
		// (Si Python lit l'entrée standard, il lira les commandes C++)
        dup2(input_pipe_[0], STDIN_FILENO);
		// Remplacer la sortie standard par l'extremité d'écriture de notre pipe
        dup2(output_pipe_[1], STDOUT_FILENO);

		// Suppression des copies car on a deja l'accès via STD...
        close(input_pipe_[0]);
        close(input_pipe_[1]);
        close(output_pipe_[0]);
        close(output_pipe_[1]);

		// Exécution des commandes
		execl(
			python_path_.c_str(),
			python_path_.c_str(),
			script_path_.c_str(),
			static_cast<char*>(nullptr)
		);

        perror("Erreur lors du lancement de Python");
        _exit(127);
    }

    // Processus parent : s'occupe de la suite du C++
	// Fermeture des extrémités utillisées par l'enfant
    close(input_pipe_[0]);
    close(output_pipe_[1]);

    input_pipe_[0] = -1;
    output_pipe_[1] = -1;

    // Évite que SIGPIPE termine Praetorium si Python s'arrête
    struct sigaction action {};
    action.sa_handler = SIG_IGN;
    sigemptyset(&action.sa_mask);
    sigaction(SIGPIPE, &action, nullptr);

    // Attente de la confirmation de connexion Python
    if (!receive_response("READY"))
    {
        std::cerr << "Le contrôleur Python n'a pas démarré correctement\n";
        stop();
        return false;
    }

    std::cout << "Contrôleur de caméra démarré\n";

    return true;
}

bool CameraController::send_command(const char* command)
{
    if (input_pipe_[1] < 0)
    {
        return false;
    }

    std::string message = std::string(command) + "\n";

    std::size_t sent = 0;

    while (sent < message.size())
    {
        ssize_t result = write(
            input_pipe_[1],
            message.data() + sent,
            message.size() - sent
        );

        if (result <= 0)
        {
            std::cerr << "Erreur lors de l'envoi d'une commande Python\n";
            return false;
        }

        sent += static_cast<std::size_t>(result);
    }

    return true;
}

bool CameraController::receive_response(const char* expected_response)
{
    if (output_pipe_[0] < 0)
    {
        return false;
    }

    std::string response;

    while (true)
    {
        pollfd descriptor {};
        descriptor.fd = output_pipe_[0];
        descriptor.events = POLLIN;

        int result = poll(&descriptor, 1, 10000);

        if (result <= 0)
        {
            std::cerr << "Aucune réponse du contrôleur Python\n";
            return false;
        }

        char character;

        ssize_t received = read(output_pipe_[0], &character, 1);

        if (received <= 0)
        {
            std::cerr << "Connexion avec le contrôleur Python perdue\n";
            return false;
        }

        if (character == '\n')
        {
            break;
        }

        response += character;
    }

    std::cout << "Python : " << response << '\n';

    return response == expected_response;
}

bool CameraController::set_privacy_mode(bool enabled)
{
    const char* command =
        enabled ? "PRIVACY_ON" : "PRIVACY_OFF";

    const char* expected_response =
        enabled ? "OK PRIVACY_ON" : "OK PRIVACY_OFF";

    if (!send_command(command))
    {
        return false;
    }

    return receive_response(expected_response);
}

void CameraController::stop()
{
	// Arrêt du processus Python
    if (process_id_ > 0 && input_pipe_[1] >= 0)
    {
        send_command("QUIT");
    }

	// Fermeture pipe parent
    if (input_pipe_[1] >= 0)
    {
        close(input_pipe_[1]);
        input_pipe_[1] = -1;
    }

    if (output_pipe_[0] >= 0)
    {
        close(output_pipe_[0]);
        output_pipe_[0] = -1;
    }

    if (process_id_ > 0)
    {
        int status = 0;
        bool finished = false;

		// Pour laisser à Python un délai raisonnable pour s'arrêter -> 20 tentatives
        for (int i = 0; i < 20; ++i)
        {
			// Attendre que le processus enfant ait terminé
            pid_t result = waitpid(process_id_, &status, WNOHANG);

            if (result == process_id_ ||
                (result == -1 && errno != EINTR))
            {
                finished = true;
                break;
            }

            std::this_thread::sleep_for(
                std::chrono::milliseconds(100)
            );
        }

		// Si après plusieurs tentative Python n'a pas finit.
        if (!finished)
        {
            kill(process_id_, SIGTERM);
            waitpid(process_id_, &status, 0);
        }

        process_id_ = -1;
    }

	// Fermeture pipe enfant
    if (input_pipe_[0] >= 0)
    {
        close(input_pipe_[0]);
        input_pipe_[0] = -1;
    }

    if (output_pipe_[1] >= 0)
    {
        close(output_pipe_[1]);
        output_pipe_[1] = -1;
    }
}
