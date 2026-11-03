#include <iostream>
#include <csignal>
#include <chrono>
#include <thread>

#include "application.hpp"

extern volatile std::sig_atomic_t stop_requested;

Application::Application(bool headless)
    : config_(loadApplicationConfig()),
      communication_(config_),
	  display_(!headless)
{
}

void Application::run()
{
    cv::Mat frame;
    cv::Mat motion_mask;

    while (!stop_requested)
    {
        // Réception des commandes TCP
        std::string received_data;

        TcpReceiveStatus status =
            communication_.receive(received_data);

        if (status == TcpReceiveStatus::DATA)
        {
            receive_buffer_ += received_data;

            std::size_t position;

			// Recherche de la fin de la commande
            while ((position = receive_buffer_.find('\n')) != std::string::npos)
            {
                std::string command = receive_buffer_.substr(0, position);
                receive_buffer_.erase(0, position + 1);

                process_received_command(command);
            }
        }
        else if (status == TcpReceiveStatus::DISCONNECTED ||
                 status == TcpReceiveStatus::ERROR)
        {
            std::cerr << "Connexion avec Vigile perdue\n";
            break;
        }

		// Tant que la camera n'est pas active on ignore la partie traitement vidéo
        if (!active_)
        {
			if (display_.process_events())
			{
				break;
			}

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        if (!camera_.read(frame))
        {
            std::cerr << "Impossible de lire une image\n";

            motion_manager_.stop();
            process_send_command("CLEAR");

            camera_.close();
            active_ = false;

            continue;
        }

        // Détection de mouvement
        bool motion_detected =
            motion_detector_.detect(frame, motion_mask);

        // Gestion de l'événement (Enregistrement d'image etc...)
        MotionState motion_state =
            motion_manager_.process(frame, motion_detected);

        // Envois de commande au STM32
        if (motion_state == MotionState::STARTED)
        {
            process_send_command("MOTION");
        }
        else if (motion_state == MotionState::ENDED)
        {
            process_send_command("CLEAR");
        }

        // Affichage de fenetres
        display_.show(frame, motion_mask);

        if (display_.process_events())
        {
            motion_manager_.stop();
            process_send_command("CLEAR");

            camera_.close();
            active_ = false;
        }
    }

    motion_manager_.stop();
    process_send_command("CLEAR");

    camera_.close();
    display_.close();
}

void Application::process_send_command(const std::string& command)
{
    if (command == "MOTION")
    {
        communication_.send("MOTION\n");
    }
    else if (command == "CLEAR")
    {
        communication_.send("CLEAR\n");
    }
    else
    {
        std::cout << "Commande inconnue\n";
    }
}

void Application::process_received_command(const std::string& command)
{
    if (command == "ACTIVATE" && !active_)
    {
        std::cout << "Activation de la surveillance\n";

        if (camera_.open(config_.camera_url))
        {
            active_ = true;
        }
        else
        {
            std::cerr << "Impossible d'ouvrir la caméra\n";
        }
    }
}
