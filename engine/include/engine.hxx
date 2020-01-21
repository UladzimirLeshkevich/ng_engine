#pragma once
#include "../../logger/include/log_manager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>

#include "../../common/geometry.hxx"

#include <chrono>
#include <cmath>
#include <string>
#include <vector>

#define LOGFILELINE __FILE__ << ":" << __LINE__
#define LOGFUNCLINE __FUNCTION__ << ":" << __LINE__

const GLenum VERTEX_SHADER = GL_VERTEX_SHADER;
const GLenum FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
const std::string INVERT_TEXTURE = "Invert texture";
const std::string FULL_SCREEN = "Full screen";
const std::string WINDOW_MODE = "Window mode";

class engine
{
public:
    engine();
    engine(const std::string& in_screen_mode_type, const int& in_width, const int& in_height);

    bool events();
    void render_triangle(const triangle& t);
    void swap_buffers();

    ~engine();

private:
    bool initialize();
    bool initialize(const std::string& screen_mode_type, const int& in_width, const int& in_height);

    const static std::string system_name;
    std::shared_ptr<Log> logger;
    SDL_Event test_event;

    SDL_Window* window = nullptr;

    //=== screen aspect ratio ===
    int width;
    int height;
    float k_screen = 1.0f; //= height / width;
    std::string screen_mode_type;

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
    int location{0};

    template <typename T>
    void load_gl_func(const char* func_name, T& result);

    void old_create_shader();

    //=== mouse ===
    bool key_MOUSE_flag = false;
    bool mouse_click = false;
    float mouse_x_pos = 0.f;
    float mouse_y_pos = 0.f;
};
