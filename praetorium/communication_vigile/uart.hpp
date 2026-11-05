#pragma once

#include <cstdint>
#include <string>

class Uart {
public:

    Uart(const std::string& device, uint32_t baudrate);
    ~Uart();

    bool send(uint8_t value);
    bool send(const std::string& data);

private:

    int fd_;
};
