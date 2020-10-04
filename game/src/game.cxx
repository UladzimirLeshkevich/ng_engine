#include "game.hxx"
#include "engine.hxx"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>

#include <dos.h>

#include <chrono>
#include <thread>

int main(int /*argc*/, char * /*argv*/[])
{
    engine ge(WINDOW_MODE, 800, 800);
    const std::string sA = "main_sys";
    std::shared_ptr<Log> logger{LogManager::get_logger(sA)};
    // logger->open_logfile("log.txt");
    logger << 100 << " test log from game " << INFO;
    std::cout << "!!!!!!!!!!!!!!!!!!!" << std::endl;

    rot_object p;

    p.set_geometry(0.f, 0.1f, 0.3f, 0.3f);

    p.set_rotatinon_paremetres(30.0f, -1);
    //p.set_speed(0.4f / 60.f);

    p.set_texture(ge.load_image("panzer_base.png"));
    ge.scale_rectangle(3.f, p.get_geometry());

    bool loop = true;

    // animation
    animation run;
    run.set_fps(2);
    run.set_number_of_frames(2);
    int run_number = 0;

    // frame timer
    float frame_delta_time{0}; //
    timer frame_timer;         //
    frame_timer.start_timer(); //

    while (loop)
    {
        loop = ge.events();

        //============ TIMERS ====================
        frame_timer.frame_begin();

        frame_delta_time = frame_timer.get_delta_time(); // !!

        //if (frame_timer.calc_delta_time_duration().count() < 16.666)          // 1000 % 60 = 16.666 FPS
        if (frame_delta_time < 16.666) // 1000 % 60 = 16.666 FPS
        {
            //Sleep(16.666-frame_delta_time);     // GPU 7 %   CPU=2%
            std::this_thread::yield(); // GPU 7 %   CPU=24%
            //delay(16.666-frame_delta_time);

            //std::this_thread::sleep_for( std::chrono::milliseconds(frame_timer.calc_delta_time_duration()) ); // GPU 5 %   CPU=0%  bad move

            //uint32_t to_sleep = 16.666 - frame_delta_time;
            //std::this_thread::sleep_for( std::chrono::milliseconds(to_sleep) ); // GPU 5 %   CPU=2%  bad move?

            continue;
        }

        time_t timeStamp = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());
        std::cout << std::ctime(&timeStamp) << std::endl;

        //============ KEYS and ACTIONS ====================
        //ge.rotate(p.get_calculaterd_speed(), p.get_geometry(), p.get_direction());
        ge.rotate_with_current_speed(p.get_speed(), p.get_geometry(), p.get_direction());

        //=== render ===
        ge.render(p.get_geometry(), p.get_texture());

        ge.swap_buffers();

        frame_timer.frame_end();
    }

    return EXIT_SUCCESS;
}
