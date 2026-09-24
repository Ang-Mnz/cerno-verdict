#include <iostream>

#include "application.hpp"

Application::Application()
    : uart_(config_.uart_device, config_.uart_baudrate)
{
}

void Application::run()
{
    if (!camera_.open())
    {
        std::cerr << "Impossible d'ouvrir la caméra\n";
        return;
    }

    cv::Mat frame;
	cv::Mat motion_mask;

    while (true)
    {
        if (!camera_.read(frame))
        {
            std::cerr << "Impossible de lire une image\n";

			motion_manager_.stop();
			process_command("CLEAR");

            break;
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
			process_command("MOTION");
		}
		else if (motion_state == MotionState::ENDED)
		{
			process_command("CLEAR");
		}

		// Affichage de fenetres
        display_.show(frame, motion_mask);

        if (display_.should_close())
        {
			motion_manager_.stop();
			process_command("CLEAR");
            break;
        }
    }

    display_.close();
}

void Application::process_command(const std::string& command)
{
    if (command == "MOTION")
    {
        uart_.send("MOTION\n");
    }
    else if (command == "CLEAR")
    {
        uart_.send("CLEAR\n");
    }
    else
    {
        std::cout << "Commande inconnue\n";
    }
}
