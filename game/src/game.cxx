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

int main(int /*argc*/, char* /*argv*/[])
{
    engine               ge(WINDOW_MODE, 800, 800);
    const std::string    sA = "main_sys";
    std::shared_ptr<Log> logger{ LogManager::get_logger(sA) };

    person p;

    p.set_geometry(0.0f, 0.5f, 0.3f, 0.3f);

    // TODO add FPS varible and getter/setter into the engine
    p.set_speed(0.4f / 60.f); // TODO  /60.f  remove from here to the function set_speed
    p.set_texture(ge.load_image("panzer_base.png"));

    bool loop = true;

    // animation
    animation run;
    run.set_fps(2);
    run.set_number_of_frames(2);
    int   run_number = 0;

    // frame timer
    float frame_delta_time{0};              //
    timer frame_timer;                      //
    frame_timer.set_start_point();          //  

    p.set_direction(left);

    //TODO add scale for limits coordinate in engine for ge(WINDOW_MODE, 800, 600);
    p.set_left_limit_coordinate(-1.f);
    p.set_right_limit_coordinate(1.f);

    while (loop)
    {
        loop = ge.events();

        //============ TIMERS ====================
        // TODO to hide this into the engine => game must be DLL ??
        frame_timer.set_frame_start_point(); 


        frame_delta_time = frame_timer.calc_delta_time(); // !!

        
        //if (frame_timer.calc_delta_time_duration().count() < 16.666)          // 1000 % 60 = 16.666 FPS
        if (frame_delta_time < 16.666)          // 1000 % 60 = 16.666 FPS
        { 
            std::this_thread::yield();
            continue;
        }
        //==============================================================================



        //============ KEYS and ACTIONS ====================    
        ge.move(p.get_speed(), p.get_geometry(), p.get_direction());

        if ( p.on_the_left_limit() )
        {
            std::cout <<"LEFT LIMIT"<<std::endl;
            p.set_direction(right);
        } 

        if( p.on_the_right_limit() )
        {
            std::cout <<"RIGHT LIMIT"<<std::endl;
            p.set_direction(left);
        }


        //=== animation ===      
        //run_number = run.current_frame_number(frame_delta_time);

        //=== render ===
        ge.render(p.get_geometry(), p.get_texture());

        ge.swap_buffers();

        frame_timer.update_start_point(); // TODO hide into the engine
    }

    return EXIT_SUCCESS;
}
