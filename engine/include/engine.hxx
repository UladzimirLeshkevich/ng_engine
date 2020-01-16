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
    const static std::string system_name;
    std::shared_ptr<Log> logger;
    SDL_Event test_event;
};
