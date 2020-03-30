#include "game.hxx"
#include "engine.hxx"
#include "game_object.hxx"
#include <iostream>

int main(int /*argc*/, char* /*argv*/[])
{
    engine ge(WINDOW_MODE, 800, 600);
    const std::string sA = "main_sys";
    std::shared_ptr<Log> logger{LogManager::get_logger(sA)};
    // logger->open_logfile("log.txt");
    logger << 100 << " jasjdfad " << INFO;
    std::cout << "!!!!!!!!!!!!!!!!!!!" << std::endl;

    triangle tr;

    tr.v[0] = {-0.8794233f, -0.5f, 0.0f, 1.0f};
    tr.v[1] = {-0.8794233f, 0.0f, 0.0f, 0.0f};
    tr.v[2] = {-0.5f, -0.5f, 1.0f, 1.0f};

    person p;
    p.set_geometry(0.f, 0.f, 0.3f, 0.3f);
    p.set_speed(0.0001f);

    bool loop = true;

    while (loop)
    {
        loop = ge.events();

        // std::cout << ge.key_A_pressed() << std::endl;

        if (ge.key_A_pressed())
        {

            std::cout << "k_screen=  " << ge.get_k_screen() << std::endl;
            // logger << ge.key_A_pressed() << "AAA" << DEBUG; //bad, to many
            // logs per one click...
        }

        if (ge.key_S_pressed())
        {
            p.set_direction(left);
            ge.move(p.get_speed(), p.get_geometry());
            // std::cout << key_A_flag << std::endl;
            // logger << ge.key_S_pressed() << "SSS" << DEBUG;
        }

        ge.render(p.get_geometry());
        ge.render(tr);
        // ge.render_triangle(tr);
        ge.swap_buffers();
    }

    // logger->close_log();
    return EXIT_SUCCESS;
}
