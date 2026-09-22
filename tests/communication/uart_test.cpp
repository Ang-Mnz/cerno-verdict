#include <cassert>
#include <iostream>

#include "communication/uart.hpp"

int main()
{
    Uart uart("/dev/ttyACM0", 115200);

    // Test d'envoi d'une commande au STM32
    assert(uart.send("MOTION\n"));

    std::cout << "Uart tests passed." << std::endl;

    return 0;
}
