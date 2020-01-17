#include "game.hxx"
#include "engine.hxx"
#include <iostream>

int main(int /*argc*/, char* /*argv*/[])
{
    const std::string sA = "main_sys";

    std::shared_ptr<Log> logger{LogManager::get_logger(sA)};
    logger->open_logfile("log.txt");
    logger << 100 << " jasjdfad " << INFO;
    std::cout << "!!!!!!!!!!!!!!!!!!!" << std::endl;

    engine ge(WINDOW_MODE, 800, 100);

    bool loop = true;

    while (loop)
    {
        loop = ge.events();
    }

    logger->close_log();
    return EXIT_SUCCESS;
}
