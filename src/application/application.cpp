#include <iostream>

#include "application.hpp"

Application::Application()
    : uart_("/dev/ttyACM0", 115200)
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
            break;
        }

		// Détection de mouvement
		bool motion_detected =
            motion_detector_.detect(frame, motion_mask);

		// Envois de commande au STM32
		if (motion_detected &&
    		(motion_events_.empty() ||
			!motion_events_.back().is_active()))
		{
			motion_events_.emplace_back();
			motion_events_.back().start(frame);
			process_command("MOTION");
		}
		else if (!motion_detected &&
         		 !motion_events_.empty() &&
         		 motion_events_.back().is_active())
		{
			motion_events_.back().end();
			storage_.save(motion_events_.back());
			process_command("CLEAR");
		}

		// Affichage de fenetres
        display_.show(frame, motion_mask);

        if (display_.should_close())
        {
            break;
        }
    }

	// Plus de mouvment à la fin du programme
	if (!motion_events_.empty() &&
		motion_events_.back().is_active())
	{
		motion_events_.back().end();
		process_command("CLEAR");
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
