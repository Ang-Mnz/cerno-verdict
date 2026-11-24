#pragma once

#include <httplib.h>
#include <thread>
#include <string>
#include <cstdint>

#include "communication_vigile/communication.hpp"

class HttpServer
{
public:
    HttpServer(const std::string& host, std::uint16_t port, Communication& communication);
    ~HttpServer();

    void start();
    void stop();

private:
    httplib::Server server_;
    std::thread thread_;

    std::string host_;
    std::uint16_t port_;

	std::mutex mutex_;
    bool started_ = false;

	Communication& communication_;
};
