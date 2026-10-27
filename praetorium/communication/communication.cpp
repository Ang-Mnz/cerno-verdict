#include "communication/communication.hpp"

#include <stdexcept>

Communication::Communication(const ApplicationConfig& config)
{
    if (config.communication_mode == CommunicationMode::UART)
    {
        uart_ = std::make_unique<Uart>(
            config.uart_device,
            config.uart_baudrate
        );
    }
    else if (config.communication_mode == CommunicationMode::TCP)
    {
        tcp_ = std::make_unique<Tcp>(
            config.tcp_host,
            config.tcp_port
        );

        if (!tcp_->connect())
        {
            throw std::runtime_error(
                "Impossible de se connecter a l'ESP32 en TCP"
            );
        }
    }
    else
    {
        throw std::runtime_error(
            "Mode de communication inconnu"
        );
    }
}

bool Communication::send(const std::string& data)
{
    if (uart_)
    {
        return uart_->send(data);
    }

    if (tcp_)
    {
        return tcp_->send(data);
    }

    return false;
}
