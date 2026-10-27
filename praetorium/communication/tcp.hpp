#pragma once

#include <cstdint>
#include <string>

class Tcp
{
public:
    Tcp(const std::string& host, std::uint16_t port);
    ~Tcp();

    bool connect();
    bool send(const std::string& data);

private:
    std::string host_;
    std::uint16_t port_;
    int socket_;
};
