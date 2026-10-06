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
    }

    if (config.camera_url.empty())
    {
        throw std::runtime_error(
            "CERNO_CAMERA_URL n'est pas définie dans .env"
        );
    }

    return config;
}
