#include "http_server.hpp"

#include <iostream>
#include <stdexcept>

HttpServer::HttpServer(
    const std::string& host,
    std::uint16_t port,
    Communication& communication
)
    : host_(host),
      port_(port),
      communication_(communication)
{
}

HttpServer::~HttpServer()
{
    stop();
}

void HttpServer::start()
{
	// Prendre et libérer automatiquement le verrou lorsqu'on sort de la portée
    std::lock_guard<std::mutex> lock(mutex_);

    if (started_) return;

    // Limite la taille des requêtes reçues à 1 Mo.
    server_.set_payload_max_length(1024 * 1024);

    // Définition de la route GET /health.
    server_.Get("/health", [](const httplib::Request&, httplib::Response& response)
    {
        response.set_content(
            R"({"component":"Praetorium","status":"UP"})",
            "application/json"
        );
    });

	// Tester vigile
	server_.Get("/vigile/health",
    [this](const httplib::Request&, httplib::Response& response)
	{
		const bool connected = communication_.is_connected();

		const std::string status = connected ? "UP" : "DOWN";

		response.set_content(
			R"({"component":"Vigile","status":")" + status + R"("})",
			"application/json"
		);
	});

    // Réservation de l'adresse et du port.
    if (!server_.bind_to_port(host_, port_))
    {
        throw std::runtime_error(
            "Impossible de réserver le port HTTP de Praetorium"
        );
    }

    started_ = true;

    // Démarrage de l'écoute dans un thread indépendant.
    thread_ = std::thread([this]()
    {
        if (!server_.listen_after_bind())
        {
            std::cerr << "Erreur pendant l'écoute HTTP\n";
        }
    });
}

void HttpServer::stop()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (!started_) return;

    server_.stop();

    if (thread_.joinable())
    {
        thread_.join();
    }

    started_ = false;
}
