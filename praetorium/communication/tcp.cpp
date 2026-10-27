#include "tcp.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>

Tcp::Tcp(const std::string& host, std::uint16_t port)
    : host_(host),
      port_(port),
      socket_(-1)
{
}

Tcp::~Tcp()
{
    if (socket_ >= 0)
    {
        close(socket_);
    }
}

bool Tcp::connect()
{
    if (socket_ >= 0)
    {
        close(socket_);
        socket_ = -1;
    }

	// Structure d'infos sur une adresse réseau
    addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    addrinfo* result = nullptr;

    const std::string port = std::to_string(port_);

	// Prépare une liste d'adresses pour tenter une connexion vers l'hote et le port
    if (getaddrinfo(host_.c_str(), port.c_str(), &hints, &result) != 0)
    {
        return false;
    }

	// On tests les differentes addrinfo qu'on a récupéré
    for (addrinfo* address = result; address != nullptr; address = address->ai_next)
    {
        // Création du socket avec les infos
		socket_ = ::socket(
            address->ai_family,
            address->ai_socktype,
            address->ai_protocol
        );

        if (socket_ < 0)
        {
            continue;
        }

		// Connexion
        if (::connect(socket_, address->ai_addr, address->ai_addrlen) == 0)
        {
            freeaddrinfo(result);
            return true;
        }

        close(socket_);
        socket_ = -1;
    }

    freeaddrinfo(result);
    return false;
}

bool Tcp::send(const std::string& data)
{
    if (socket_ < 0)
    {
        return false;
    }

    std::size_t total_sent = 0;

    while (total_sent < data.size())
    {
        const ssize_t sent = ::send(
            socket_,
            data.data() + total_sent,
            data.size() - total_sent,
            0
        );

        if (sent <= 0)
        {
            return false;
        }

        total_sent += static_cast<std::size_t>(sent);
    }

    return true;
}
