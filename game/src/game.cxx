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

    person p, p2;
    p.set_geometry(0.f, 0.1f, 0.3f, 0.3f);
    p2.set_geometry(0.5f, 0.5f, 0.4f, 0.4f);
    p.set_speed(0.001f);
    p.set_texture(ge.load_image("panzer_base.png"));
    //p2.set_texture(ge.load_image("robot_2.png"));

    p2.set_texture_to_sprite(ge.load_image("robot_2.png"));
    p2.set_texture_to_sprite(ge.load_image("robot_1.png"));

    bool loop = true;

    // animation
    animation run;
    run.set_fps(2);
    run.set_number_of_frames(2);
    int run_number = 0;
    timer ani_timer;
    float delta_time = 0.f;

    while (loop)
    {
        loop = ge.events();

        //============ TIMERS ====================
        delta_time = ani_timer.elapsed();

        if (ge.key_A_pressed())
        {
            p.set_direction(left);
            ge.move(p.get_speed(), p.get_geometry(), p.get_direction());
            // std::cout << "k_screen=  " << ge.get_k_screen() << std::endl;
            // logger << ge.key_A_pressed() << "AAA" << DEBUG; //bad, to many
            // logs per one click...
        }

        if (ge.key_S_pressed())
        {
            p.set_direction(down);
            ge.move(p.get_speed(), p.get_geometry(), p.get_direction());
        }

        if (ge.key_D_pressed())
        {
            p.set_direction(right);
            ge.move(p.get_speed(), p.get_geometry(), p.get_direction());
        }

        if (ge.key_W_pressed())
        {
            p.set_direction(up);
            // ge.invert_texture_by_y_p(p.get_geometry());
            ge.move(p.get_speed(), p.get_geometry(), p.get_direction());
        }

        if (ge.key_Q_pressed())
        {
            p.set_direction(up_left);
            ge.move(p.get_speed(), p.get_geometry(), p.get_direction());
        }

        if (ge.key_LCTRL_pressed())
        {
            // ge.set_view_mode(front_view);
            ge.switch_view_mode();
        }

        // ge.render(p.get_geometry());
        // ge.render_textured_rectangle(p.get_geometry(), ); // lvi need debug here !!
        // ge.render_textured_rectangle(p.get_geometry(), p.get_texture());
        // ge.render(tr);

        // ge.render_triangle(tr);

        //=== animation ===
        run.restart();
        run_number = run.current_frame_number(delta_time);
        ge.render(p2.get_geometry(),
                  p2.get_from_sprite(run_number));

        ge.render(p.get_geometry(), p.get_texture());
        //ge.render(p2.get_geometry(), p2.get_texture());

        ge.swap_buffers();
    }

    // logger->close_log();
    return EXIT_SUCCESS;
}
