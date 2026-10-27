#include "application/application_config.hpp"

#include <cstdlib>
#include <stdexcept>
#include <fstream>

ApplicationConfig loadApplicationConfig()
{
    ApplicationConfig config;

    std::ifstream file(".env");

    if (!file.is_open())
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier .env");
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        const std::size_t separator = line.find('=');

        if (separator == std::string::npos)
        {
            continue;
        }

        const std::string key = line.substr(0, separator);
        const std::string value = line.substr(separator + 1);

        if (key == "CERNO_CAMERA_URL")
        {
            config.camera_url = value;
        }
		else if (key == "COMMUNICATION_MODE")
		{
			if (value == "UART")
			{
				config.communication_mode = CommunicationMode::UART;
			}
			else if (value == "TCP")
			{
				config.communication_mode = CommunicationMode::TCP;
			}
			else
			{
				throw std::runtime_error(
					"COMMUNICATION_MODE doit être UART ou TCP"
				);
			}
		}
		else if (key == "UART_DEVICE")
		{
			config.uart_device = value;
		}
		else if (key == "UART_BAUDRATE")
		{
			config.uart_baudrate = std::stoul(value);
		}
		else if (key == "TCP_HOST")
		{
			config.tcp_host = value;
		}
		else if (key == "TCP_PORT")
		{
			config.tcp_port = std::stoul(value);
		}
    }

    if (config.camera_url.empty())
    {
        throw std::runtime_error(
            "CERNO_CAMERA_URL n'est pas définie dans .env"
        );
    }

    return config;
}
