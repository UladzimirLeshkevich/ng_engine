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
    engine ge(WINDOW_MODE, 600, 1200);
    const std::string sA = "main_sys";
    std::shared_ptr<Log> logger{LogManager::get_logger(sA)};
    // logger->open_logfile("log.txt");
    logger << 100 << " test log from game " << INFO;
    std::cout << "!!!!!!!!!!!!!!!!!!!" << std::endl;

    person p;

    p.set_world_geometry(1800.f, 1500.f, 200.f, 200.f);
    p.set_texture(ge.load_image("panzer_base.png"));
    //ge.scale_rectangle(3.f, p.get_geometry());

    std::cerr << "p = " << p.get_geometry().v[0].x << " " << p.get_geometry().v[0].y << "\n!!";

    // frame timer
    float frame_delta_time{0}; //
    timer frame_timer;         //
    frame_timer.start_timer(); //

    bool loop = true;
    while (loop)
    {
        loop = ge.events();

        //============ TIMERS ====================
        frame_timer.frame_begin();
        frame_delta_time = frame_timer.get_delta_time(); // !!
        if (frame_delta_time < 16.666)                   // 1000 % 60 = 16.666 FPS
        {
            //Sleep(16.666-frame_delta_time);     // GPU 7 %   CPU=2%
            std::this_thread::yield(); // GPU 7 %   CPU=24%

            continue;
        }

        // time_t timeStamp = std::chrono::system_clock::to_time_t(
        //     std::chrono::system_clock::now());
        // std::cout << std::ctime(&timeStamp) << std::endl;

        //============ KEYS and ACTIONS ====================
        //ge.rotate(p.get_calculaterd_speed(), p.get_geometry(), p.get_direction());
        //ge.rotate_with_current_speed(p.get_speed(), p.get_geometry(), p.get_direction());

        //=== render ===
        ge.render(p.get_geometry(), p.get_texture());

        //ge.render(p.get_geometry());
        ge.swap_buffers();

        //=== timer reset ===
        frame_timer.frame_end();
    }

    return EXIT_SUCCESS;
}
