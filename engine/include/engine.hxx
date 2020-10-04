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

#include "../../common/geometry.hxx"
#include "animation.hxx"
#include "game_object.hxx"
#include "timer.hxx"

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
const std::string top_view{"top_view"};
const std::string front_view{"front_view"};

// rotation direction
#define CKW -1 // clockwise
#define CCKW 1 // contraclockwise

class engine
{
public:
    engine();
    engine(const std::string &in_screen_mode_type, const float &in_width,
           const float &in_height);

    bool events();

    void swap_buffers();

    void set_view_mode(const std::string &in_mode);

    void switch_view_mode();

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

    void render(const rectangle &r);
    void render(const triangle &t);

    ~engine();

    float get_k_screen() { return k_screen; }

    // mooving
    void move(float speed, rectangle &geometry);

    void move(float speed, rectangle &geometry, direction dir);

    void move_foward(float speed, rectangle &geometry);

    void move_backward(float speed, rectangle &geometry);

    void rotate(float value, rectangle &geometry, int direction);

    void rotate_with_current_speed(float value, rectangle &geometry, int direction); // rotate per minute

    void normalize_vector(point &v);

    // textures
    GLuint load_image(std::string filename);
    void render_textured_rectangle(const rectangle &r, GLint texture_number);
    void render(const rectangle &r, GLint texture_number);

    void scale_triangle(float fscale_valueX, float fscale_valueY, triangle &t)
    {

        float x0 = t.v[0].x;
        float y0 = t.v[0].y;

        float x1 = t.v[1].x;
        float y1 = t.v[1].y;

        float x2 = t.v[2].x;
        float y2 = t.v[2].y;

        t.v[0].x = (fscale_valueX * x0 + 0 * y0 + 0 * 1);
        t.v[0].y = (0 * x0 + fscale_valueY * y0 + 0 * 1);

        t.v[1].x = (fscale_valueX * x1 + 0 * y1 + 0 * 1);
        t.v[1].y = (0 * x1 + fscale_valueY * y1 + 0 * 1);

        t.v[2].x = (fscale_valueX * x2 + 0 * y2 + 0 * 1);
        t.v[2].y = (0 * x2 + fscale_valueY * y2 + 0 * 1);
    }

    void scale_rectangle(float fscale_valueX, float fscale_valueY, rectangle &r)
    {
        float x0 = r.v[0].x;
        float y0 = r.v[0].y;

        float x1 = r.v[1].x;
        float y1 = r.v[1].y;

        float x2 = r.v[2].x;
        float y2 = r.v[2].y;

        float x3 = r.v[3].x;
        float y3 = r.v[3].y;

        r.v[0].x = (fscale_valueX * x0 + 0 * y0 + 0 * 1);
        r.v[0].y = (0 * x0 + fscale_valueY * y0 + 0 * 1);

        r.v[1].x = (fscale_valueX * x1 + 0 * y1 + 0 * 1);
        r.v[1].y = (0 * x1 + fscale_valueY * y1 + 0 * 1);

        r.v[2].x = (fscale_valueX * x2 + 0 * y2 + 0 * 1);
        r.v[2].y = (0 * x2 + fscale_valueY * y2 + 0 * 1);

        r.v[3].x = (fscale_valueX * x3 + 0 * y3 + 0 * 1);
        r.v[3].y = (0 * x3 + fscale_valueY * y3 + 0 * 1);
    }

    void scale_rectangle(float fscale_value, rectangle &r)
    {
        float x0 = r.v[0].x;
        float y0 = r.v[0].y;

        float x1 = r.v[1].x;
        float y1 = r.v[1].y;

        float x2 = r.v[2].x;
        float y2 = r.v[2].y;

        float x3 = r.v[3].x;
        float y3 = r.v[3].y;

        r.v[0].x = (fscale_value * x0);
        r.v[0].y = (fscale_value * y0);

        r.v[1].x = (fscale_value * x1);
        r.v[1].y = (fscale_value * y1);

        r.v[2].x = (fscale_value * x2);
        r.v[2].y = (fscale_value * y2);

        r.v[3].x = (fscale_value * x3);
        r.v[3].y = (fscale_value * y3);
    }

private:
    bool initialize();
    bool initialize(const std::string &screen_mode_type, const float &in_width,
                    const float &in_height);

    template <typename T>
    T scale_to_screen(T input)
    {
        input.v[0].x = input.v[0].x * k_screen;
        input.v[1].x = input.v[1].x * k_screen;
        input.v[2].x = input.v[2].x * k_screen;
        input.v[3].x = input.v[3].x * k_screen;
        // input.v[4].x = input.v[4].x * k_screen; // lvi ??

        return input;
    }

    void trans_matrix(float fdeltaX, float fdeltaY, rectangle &r);

    void move_to_direction(const float speed, rectangle &geometry);

    void rotate_matrix(float frotate_angle, rectangle &r);

    const static std::string system_name;
    std::shared_ptr<Log> logger;
    SDL_Event test_event;

    SDL_Window *window = nullptr;

    //=== screen aspect ratio ===
    float width;
    float height;
    float k_screen; //= height / width;
    std::string screen_mode_type;

    //=== sound varibles ===
    Mix_Music *music;
    Mix_Chunk *music_chunk;
    // int channel;

    //=== keyboard flags===
    bool key_W_flag{false};
    bool key_S_flag{false};
    bool key_A_flag{false};
    bool key_D_flag{false};
    bool key_SPACE_flag{false};
    bool key_LCTRL_flag{false};
    bool key_ENTER_flag{false};
    bool key_Esc_flag{false};
    bool key_Q_flag{false};
    bool key_E_flag{false};

    //=== openGL ===
    GLuint program{0};
    int location{0};

    template <typename T>
    void load_gl_func(const char *func_name, T &result);

    void old_create_shader();

    void render_triangle(const triangle &t);
    void render_rectangle(const rectangle &r);

    //=== mouse ===
    bool key_MOUSE_flag{false};
    bool mouse_click{false};
    float mouse_x_pos{0.f};
    float mouse_y_pos{0.f};

    std::string resources{"res/"};

    //=== textures ===
    GLuint texture_id{0};

    rectangle invert_texture_by_x(rectangle r); // lvi delete
    rectangle invert_texture_by_y(rectangle r); // lvi delete
    void texture_look_left(rectangle &r);
    void texture_look_right(rectangle &r);
    void texture_look_down(rectangle &r);
    void texture_look_up(rectangle &r);
    void texture_look_right_rotate(rectangle &r);
    void texture_look_left_rotate(rectangle &r);

    std::string view_mode; // top or front => for choosing changing textures
                           // coordinates bihavior

    float m_fps{60};
};
