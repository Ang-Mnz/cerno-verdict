#include <iostream>

#include "application.hpp"

Application::Application()
    : uart_("/dev/ttyACM0", 115200)
{
}

void Application::run()
{
    std::string command;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "q")
        {
            break;
        }

        process_command(command);
    }
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
