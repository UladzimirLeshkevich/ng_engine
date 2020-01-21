#include "game.hxx"
#include "engine.hxx"
#include <iostream>

int main(int /*argc*/, char* /*argv*/[])
{
    engine ge(WINDOW_MODE, 800, 200);
    const std::string sA = "main_sys";
    std::shared_ptr<Log> logger{LogManager::get_logger(sA)};
    //logger->open_logfile("log.txt");
    logger << 100 << " jasjdfad " << INFO;
    std::cout << "!!!!!!!!!!!!!!!!!!!" << std::endl;

    triangle tr;

    tr.v[0] = {-0.8794233f, -0.5f, 0.0f, 1.0f};
    tr.v[1] = {-0.8794233f, 0.0f, 0.0f, 0.0f};
    tr.v[2] = {-0.5f, -0.5f, 1.0f, 1.0f};

    bool loop = true;

    while (loop)
    {
        loop = ge.events();
        ge.render_triangle(tr);
        ge.swap_buffers();
    }

    //logger->close_log();
    return EXIT_SUCCESS;
}
