#pragma once

#include <memory>
#include <string>

#include "application/application_config.hpp"
#include "communication/uart.hpp"
#include "communication/tcp.hpp"

class Communication
{
public:
    explicit Communication(const ApplicationConfig& config);

    bool send(const std::string& data);

private:
    std::unique_ptr<Uart> uart_;
    std::unique_ptr<Tcp> tcp_;
};
