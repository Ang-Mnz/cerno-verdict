#include <iostream>
#include <string>

#include "communication/uart.hpp"

int main()
{
    Uart uart("/dev/ttyACM0", 115200);

    std::string command;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "q")
        {
            break;
        }

        if (command == "MOTION")
        {
            uart.send("MOTION\n");
        }
        else if (command == "CLEAR")
        {
            uart.send("CLEAR\n");
        }
        else
        {
            std::cout << "Commande inconnue\n";
        }
    }

    return 0;
}
