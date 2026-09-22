#pragma once

#include <string>

#include "communication/uart.hpp"

class Application
{
public:
    Application();

    void run();

private:
    Uart uart_;

    void process_command(const std::string& command);
};
