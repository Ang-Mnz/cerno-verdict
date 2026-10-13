#include <csignal>

#include "application/application.hpp"

volatile std::sig_atomic_t stop_requested = 0;

namespace
{
    void handle_signal(int)
    {
        stop_requested = 1;
    }
}

int main(int argc, char* argv[])
{
	std::signal(SIGTERM, handle_signal);
	std::signal(SIGINT, handle_signal);

    bool headless = false;

    for (int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]) == "--headless")
        {
            headless = true;
        }
        else
        {
            std::cerr << "Argument inconnu : " << argv[i] << '\n';
            return 1;
        }
    }

    Application app(headless);
    app.run();

    return 0;
}
