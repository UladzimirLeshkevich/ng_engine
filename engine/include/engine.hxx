#pragma once
//#include "../../logger/include/log.h"
#include "../../logger/include/log_manager.h"
#include <SDL2/SDL.h>
#include <iostream>

class engine
{
    static const std::string sA;
    std::shared_ptr<Log>     logger{ LogManager::get_logger(sA) };
    SDL_Event                test_event;

public:
    //================== метод инициализации SDL2 ==========================
    bool initialize();

    //================== метод обработки событий ===========================
    bool events();

    //================== конструктор ===============================

    engine() { initialize(); }

    //================== деструктор ===============================
    ~engine();
};

const std::string engine::sA = "engine_system";
