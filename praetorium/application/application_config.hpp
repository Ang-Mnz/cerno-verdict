#pragma once

#include <cstdint>
#include <string>

struct ApplicationConfig
{
    std::string uart_device = "/dev/ttyUSB0";
    std::uint32_t uart_baudrate = 115200;

	std::string camera_url;
};

ApplicationConfig loadApplicationConfig();
