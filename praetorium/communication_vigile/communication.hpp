#pragma once

#include <memory>
#include <string>

#include "application/application_config.hpp"
#include "communication_vigile/uart.hpp"
#include "communication_vigile/tcp.hpp"

class Communication
{
public:
    explicit Communication(const ApplicationConfig& config);

    bool send(const std::string& data);
	TcpReceiveStatus receive(std::string& data);

private:
    std::unique_ptr<Uart> uart_;
    std::unique_ptr<Tcp> tcp_;
};
