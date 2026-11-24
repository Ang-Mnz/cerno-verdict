#pragma once

#include <cstdint>
#include <string>

enum class CommunicationMode
{
    UART,
    TCP
};

struct ApplicationConfig
{
	CommunicationMode communication_mode = CommunicationMode::UART;

    std::string uart_device = "/dev/ttyUSB0";
    std::uint32_t uart_baudrate = 115200;

	std::string tcp_host = "192.168.1.41";
	std::uint16_t tcp_port = 5000;

	std::string http_host = "127.0.0.1";
	std::uint16_t http_port = 8081;

	std::string camera_url;

    std::string python_path;
    std::string camera_controller_path;

	std::uint32_t camera_idle_timeout_seconds = 10;
};

ApplicationConfig loadApplicationConfig();
