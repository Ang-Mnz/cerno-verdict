#include "application/application.hpp"

int main(int argc, char* argv[])
{
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
