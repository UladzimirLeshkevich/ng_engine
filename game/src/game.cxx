#include "game.hxx"
#include "engine.hxx"
#include <iostream>

int main(int /*argc*/, char* /*argv*/[])
{
    engine               ge(WINDOW_MODE, 800, 600);
    const std::string    sA = "main_sys";
    std::shared_ptr<Log> logger{ LogManager::get_logger(sA) };
    // logger->open_logfile("log.txt");
    logger << 100 << " jasjdfad " << INFO;
    std::cout << "!!!!!!!!!!!!!!!!!!!" << std::endl;

    triangle tr;

    tr.v[0] = { -0.8794233f, -0.5f, 0.0f, 1.0f };
    tr.v[1] = { -0.8794233f, 0.0f, 0.0f, 0.0f };
    tr.v[2] = { -0.5f, -0.5f, 1.0f, 1.0f };

    person p, p2, p3;
    person xp_ym, xm_ym, xm_yp, zero;

    xp_ym.set_geometry(0.5f, -0.5f, 0.4f, 0.4f);
    xm_ym.set_geometry(-0.5f, -0.5f, 0.4f, 0.4f);
    xm_yp.set_geometry(-0.5f, 0.5f, 0.4f, 0.4f);
    zero.set_geometry(0.0f, 0.0f, 0.4f, 0.4f);

    p.set_geometry(0.f, 0.1f, 0.3f, 0.3f);
    p2.set_geometry(0.5f, 0.5f, 0.4f, 0.4f);
    p3.set_geometry(-0.5f, -0.5f, 0.3f, 0.4f);
    p.set_speed(0.001f);
    p.set_texture(ge.load_image("panzer_base.png"));
    // p2.set_texture(ge.load_image("robot_2.png"));

    p2.set_texture_to_sprite(ge.load_image("robot_2.png"));
    p2.set_texture_to_sprite(ge.load_image("robot_1.png"));

    p3.set_texture(ge.load_image("krita1.png"));
    // p3.set_texture_to_sprite(ge.load_image("an1.png"));

    bool loop = true;

    // animation
    animation run;
    run.set_fps(2);
    run.set_number_of_frames(2);
    int   run_number = 0;
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
            ge.rotate(0.01f, p2.get_geometry(), CCKW);
            ge.rotate(0.01f, p.get_geometry(), CCKW);
        }

        if (ge.key_E_pressed())
        {
            ge.rotate(0.01f, p2.get_geometry(), CKW);
            ge.rotate(0.01f, p.get_geometry(), CKW);
        }

        if (ge.key_LCTRL_pressed())
        {
            // ge.set_view_mode(front_view);
            ge.switch_view_mode();
        }

        if (ge.key_SPACE_pressed())
        {
            // p.set_direction(toward);
            // ge.move(p.get_speed(), p.get_geometry(), p.get_direction());

            ge.move_foward(p.get_speed(), p.get_geometry());
        }

        if (ge.key_ENTER_pressed())
        {
            // p.set_direction(backward);
            // ge.move(p.get_speed(), p.get_geometry(), p.get_direction());

            ge.move_backward(p.get_speed(), p.get_geometry());
        }

        //=== animation ===
        run.restart();
        run_number = run.current_frame_number(delta_time);
        ge.render(p2.get_geometry(), p2.get_from_sprite(run_number));

        ge.render(p.get_geometry(), p.get_texture());

        ge.swap_buffers();
    }

    // logger->close_log();
    return EXIT_SUCCESS;
}
