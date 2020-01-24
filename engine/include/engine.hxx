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

extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLVALIDATEPROGRAMPROC glValidateProgram;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLACTIVETEXTUREPROC glActiveTexture_;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

const GLenum VERTEX_SHADER = GL_VERTEX_SHADER;
const GLenum FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
const std::string INVERT_TEXTURE = "Invert texture";
const std::string FULL_SCREEN = "Full screen";
const std::string WINDOW_MODE = "Window mode";

class engine
{
public:
    engine();
    engine(const std::string& in_screen_mode_type, const float& in_width, const float& in_height);

    bool events();

    void swap_buffers();

    //=== keyboard ===
    bool key_W_pressed();
    bool key_S_pressed();
    bool key_A_pressed();
    bool key_D_pressed();
    bool key_SPACE_pressed();
    bool key_LCTRL_pressed();
    bool key_ENTER_pressed();
    bool key_Esc_pressed();
    bool key_Q_pressed();
    bool key_E_pressed();

    void render(const rectangle& r);
    void render(const triangle& t);

    ~engine();

    float get_k_screen() { return k_screen; }

private:
    bool initialize();
    bool initialize(const std::string& screen_mode_type, const float& in_width, const float& in_height);

    //    void scale_to_screen(triangle& t)
    //    {
    //        float k = height / width;
    //        t.v[0].x = t.v[0].x * k;
    //        t.v[1].x = t.v[1].x * k;
    //        t.v[2].x = t.v[2].x * k;
    //    }

    //    void scale_to_screen(rectangle& r)
    //    {
    //        float k = height / width;
    //        r.v[0].x = r.v[0].x * k;
    //        r.v[1].x = r.v[1].x * k;
    //        r.v[2].x = r.v[2].x * k;
    //        r.v[3].x = r.v[3].x * k;
    //    }

    //    triangle scale_to_screen(triangle t)
    //    {
    //        t.v[0].x = t.v[0].x * k_screen;
    //        t.v[1].x = t.v[1].x * k_screen;
    //        t.v[2].x = t.v[2].x * k_screen;

    //        logger << "scale_to_screen(triangle t) with k_screen=" << k_screen << DEBUG;

    //        return t;
    //    }

    //    rectangle scale_to_screen(rectangle r)
    //    {
    //        r.v[0].x = r.v[0].x * k_screen;
    //        r.v[1].x = r.v[1].x * k_screen;
    //        r.v[2].x = r.v[2].x * k_screen;
    //        r.v[3].x = r.v[3].x * k_screen;

    //        logger << "scale_to_screen(rectangle r) with k_screen=" << k_screen << DEBUG;

    //        return r;
    //    }

    template <typename T>
    T scale_to_screen(T input)
    {
        input.v[0].x = input.v[0].x * k_screen;
        input.v[1].x = input.v[1].x * k_screen;
        input.v[2].x = input.v[2].x * k_screen;
        input.v[3].x = input.v[3].x * k_screen;

        logger << "scale_to_screen(T input) with k_screen=" << k_screen << DEBUG;

        return input;
    }

    const static std::string system_name;
    std::shared_ptr<Log> logger;
    SDL_Event test_event;

    SDL_Window* window = nullptr;

    //=== screen aspect ratio ===
    float width;
    float height;
    float k_screen; //= height / width;
    std::string screen_mode_type;

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

    void render_triangle(const triangle& t);
    void render_rectangle(const rectangle& r);

    //=== mouse ===
    bool key_MOUSE_flag = false;
    bool mouse_click = false;
    float mouse_x_pos = 0.f;
    float mouse_y_pos = 0.f;
};
