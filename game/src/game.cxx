#include "game.hxx"
#include "engine.hxx"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>

#include <chrono>
#include <thread>

int main(int /*argc*/, char* /*argv*/[])
{
    engine               ge(WINDOW_MODE, 800, 600);
    const std::string    sA = "main_sys";
    std::shared_ptr<Log> logger{ LogManager::get_logger(sA) };
    // logger->open_logfile("log.txt");
    logger << 100 << " test log from game " << INFO;
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
    p.set_speed(0.1f / 60.f);
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

    // frame timer

    timer frame_timer;
    float frame_time = 0.f;

    //===============================================================
    // OM
    using clock_timer = std::chrono::high_resolution_clock;
    using nano_sec    = std::chrono::nanoseconds;
    using milli_sec   = std::chrono::milliseconds;
    using time_point  = std::chrono::time_point<clock_timer, nano_sec>;
    clock_timer timer;
    time_point  start = timer.now();
    //===============================================================

    while (loop)
    {
        loop = ge.events();

        time_point end_last_frame = timer.now(); // OM

        //==================================================
        // OM
        milli_sec frame_delta =
            std::chrono::duration_cast<milli_sec>(end_last_frame - start);

        // std::cout << "frame_delta = " << frame_delta << std::endl;

        if (frame_delta.count() < 16.666) // 1000 % 60 = 16.666 FPS
        {
            std::this_thread::yield(); // too fast, give other apps CPU time
            continue;                  // wait till more time
        }

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
            ge.rotate(0.1f, p2.get_geometry(), CCKW);
            ge.rotate(0.1f, p.get_geometry(), CCKW);
        }

        if (ge.key_E_pressed())
        {
            ge.rotate(0.1f, p2.get_geometry(), CKW);
            ge.rotate(0.1f, p.get_geometry(), CKW);
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

        //==================================================
        frame_time = frame_timer.elapsed();

        time_t timeStamp = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());
        std::cout << std::ctime(&timeStamp) << std::endl;

        std::cout << frame_time << std::endl;

        //        if (frame_time * 1000.f < 16.666)
        //        {
        //            std::cout << 16 - frame_time * 1000.f << std::endl;
        //            Sleep(16.666 - frame_time * 1000.f);

        //            // std::this_thread::yield(); // too fast, give other apps
        //            CPU time continue;
        //        }

        ge.swap_buffers();

        start = end_last_frame; // OM

        frame_timer.reset();
    }

    // logger->close_log();
    return EXIT_SUCCESS;
}
