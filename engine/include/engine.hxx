#pragma once
#include "../../logger/include/log_manager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>

#include <chrono>
#include <cmath>
#include <string>
#include <vector>

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

    SDL_Window* window = nullptr;

    //=== screen aspect ratio ===
    float k_screen = 1.0f; //= height / width;

    //==== mooving speed X Y ====
    float speed_to_right = 0.0f;
    float speed_to_left = 0.0f;
    float speed_to_up = 0.0f;
    float speed_to_down = 0.0f;
    float speed_to_right_value = 0.0f;
    float speed_to_left_value = 0.0f;
    float speed_to_up_value = 0.0f;
    float speed_to_down_value = 0.0f;

    //=== sound varibles ===
    Mix_Music* music;
    Mix_Chunk* music_chunk;
    // int channel;

    //=== keyboard flags===
    bool key_W_flag = false;
    bool key_S_flag = false;
    bool key_A_flag = false;
    bool key_D_flag = false;
    bool key_SPACE_flag = false;
    bool key_LCTRL_flag = false;
    bool key_ENTER_flag = false;
    bool key_Esc_flag = false;
    bool key_Q_flag = false;
    bool key_E_flag = false;


    //=== openGL ===
    GLuint program = 0;

    //=== mouse ===
    bool key_MOUSE_flag = false;
    bool mouse_click = false;
    float mouse_x_pos = 0.f;
    float mouse_y_pos = 0.f;
};
