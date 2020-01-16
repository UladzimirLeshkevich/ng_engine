#pragma once
#include "../../logger/include/log_manager.h"
#include <SDL2/SDL.h>
#include <iostream>

class engine
{
public:
    engine();

    bool initialize();

    bool events();

    ~engine();

private:
    std::shared_ptr<Log> logger{LogManager::get_logger("engine_sys")};
    SDL_Event test_event;
};
