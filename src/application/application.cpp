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

    while (true)
    {
        if (!camera_.read(frame))
        {
            std::cerr << "Impossible de lire une image\n";
            break;
        }

        if (motion_detector_.detect(frame))
        {
            std::cout << "Mouvement détecté !" << std::endl;
        }

        cv::imshow("Cerno Verdict", frame);

        int key = cv::waitKey(1);

        if (key == 'q' || key == 27)
        {
            break;
        }
    }

    cv::destroyAllWindows();
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
