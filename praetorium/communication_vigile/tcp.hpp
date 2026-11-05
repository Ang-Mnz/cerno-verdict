#pragma once

#include <cstdint>
#include <string>

enum class TcpReceiveStatus
{
    DATA,
    NO_DATA_AVAILABLE,
    DISCONNECTED,
    ERROR
};

class Tcp
{
public:
    Tcp(const std::string& host, std::uint16_t port);
    ~Tcp();

    bool connect();
    bool send(const std::string& data);
	TcpReceiveStatus receive(std::string& data);

private:
    std::string host_;
    std::uint16_t port_;
    int socket_;
};
