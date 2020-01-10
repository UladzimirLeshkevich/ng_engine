#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>
#include <array>
#include <iostream>
#include <vector>

PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
PFNGLDELETESHADERPROC glDeleteShader = nullptr;
PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = nullptr;
PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = nullptr;

template <typename T>
static void
load_gl_func(const char* func_name, T& result)
{
    void* gl_pointer = SDL_GL_GetProcAddress(func_name);
    result = reinterpret_cast<T>(gl_pointer);
    std::cout << result << "\n";
    if (nullptr == gl_pointer)
    {
        throw std::runtime_error(std::string("can't load GL function") + func_name);
    }
    result = reinterpret_cast<T>(gl_pointer);
}

struct vertex
{
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
};

struct triangle
{
    triangle()
    {
        v[0] = vertex();
        v[1] = vertex();
        v[2] = vertex();
    }
    vertex v[3];
};

std::istream&
operator>>(std::istream& is, vertex& v)
{
    is >> v.x;
    is >> v.y;
    is >> v.z;
    return is;
}

//============= Класс ==================================================
class engine
{

    SDL_Window* window = nullptr;
    GLuint program = 0;

    SDL_Event test_event;

public:
    //================== метод инициализации SDL2 ==========================
    bool initialize()
    {
        if ((SDL_Init(SDL_INIT_EVERYTHING)) != 0)
        {
            const char* err_message = SDL_GetError();
            std::cerr << "error: failed call SDL_Init: " << err_message << std::endl;
            return EXIT_FAILURE;
        }

        window = SDL_CreateWindow("title",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  480,
                                  480,
                                  ::SDL_WINDOW_OPENGL);

        if (window == nullptr)
        {
            std::cerr << "error: failed call SDL_CreateWindow: " << std::endl;
            SDL_Quit();
            return EXIT_FAILURE;
        }

        SDL_GLContext gl_context = SDL_GL_CreateContext(window);
        SDL_assert(gl_context != nullptr);
        //==========================================================================
        load_gl_func("glCreateShader", glCreateShader);
        load_gl_func("glShaderSource", glShaderSource);
        load_gl_func("glCompileShader", glCompileShader);
        load_gl_func("glGetShaderiv", glGetShaderiv);
        load_gl_func("glGetShaderInfoLog", glGetShaderInfoLog);
        load_gl_func("glDeleteShader", glDeleteShader);
        load_gl_func("glCreateProgram", glCreateProgram);
        load_gl_func("glAttachShader", glAttachShader);
        load_gl_func("glBindAttribLocation", glBindAttribLocation);
        load_gl_func("glLinkProgram", glLinkProgram);
        load_gl_func("glGetProgramiv", glGetProgramiv);
        load_gl_func("glGetProgramInfoLog", glGetProgramInfoLog);
        load_gl_func("glDeleteProgram", glDeleteProgram);
        load_gl_func("glUseProgram", glUseProgram);
        load_gl_func("glVertexAttribPointer", glVertexAttribPointer);
        load_gl_func("glEnableVertexAttribArray", glEnableVertexAttribArray);
        load_gl_func("glValidateProgram", glValidateProgram);

        GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);

        std::string vertex_shader_src =
            "attribute vec3 a_position;varying vec4 v_position;void "
            "main(){v_position "
            "= vec4(a_position, 1.0);gl_Position = v_position;}";

        const char* source = vertex_shader_src.data();
        glShaderSource(vert_shader, 1, &source, nullptr);

        glCompileShader(vert_shader);

        GLint compiled_status = 0;
        glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &compiled_status);

        if (compiled_status == 0)
        {
            GLint info_len = 0;
            glGetShaderiv(vert_shader, GL_INFO_LOG_LENGTH, &info_len);

            std::vector<char> info_chars(static_cast<size_t>(info_len));
            glGetShaderInfoLog(vert_shader, info_len, nullptr, info_chars.data());

            glDeleteShader(vert_shader);

            std::string shader_type_name = "vertex";
        }

        // create fragment shader
        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

        std::string fragment_shader_src =
            "varying vec4 v_position;void main(){if (v_position.z >= 0.0){float "
            "light_green = 0.5 + v_position.z / 2.0;gl_FragColor = vec4(0.0, "
            "light_green, 0.0, 1.0);} else{float dark_green = 0.5 - (v_position.z / "
            "-2.0);}}";
        source = fragment_shader_src.data();
        glShaderSource(fragment_shader, 1, &source, nullptr);

        glCompileShader(fragment_shader);

        compiled_status = 0;
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compiled_status);

        if (compiled_status == 0)
        {
            GLint info_len = 0;
            glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &info_len);

            std::vector<char> info_chars(static_cast<size_t>(info_len));
            glGetShaderInfoLog(fragment_shader, info_len, nullptr, info_chars.data());

            glDeleteShader(fragment_shader);
        }

        // now create program and attach vertex and fragment shaders
        program = glCreateProgram();
        glAttachShader(program, vert_shader);
        glAttachShader(program, fragment_shader);

        // bind attribute location
        glBindAttribLocation(program, 0, "a_position");

        // link program after binding attribute locations
        glLinkProgram(program);

        // turn on rendering with just created shader program
        glUseProgram(program);

        //=====================================================================

        return EXIT_SUCCESS;
    }

    //================== метод обработки событий ===========================
    bool events()
    {
        while (SDL_PollEvent(&test_event))
        {

            if (test_event.type == SDL_KEYDOWN)
            {
                switch (test_event.key.keysym.sym)
                {
                case SDLK_w:
                    std::cout << " W is pressed " << '\n';
                    break;
                case SDLK_s:
                    std::cout << " S is pressed " << '\n';
                    break;
                case SDLK_a:
                    std::cout << " A is pressed " << '\n';
                    break;
                case SDLK_d:
                    std::cout << " D is pressed " << '\n';
                    break;
                case SDLK_LCTRL:
                    std::cout << " BUTTON_ONE is pressed " << '\n';
                    break;
                case SDLK_SPACE:
                    std::cout << " BUTTON_TWO is pressed " << '\n';
                    break;
                case SDLK_RETURN:
                    std::cout << " START is pressed " << '\n';
                    break;
                case SDLK_ESCAPE:
                    std::cout << " ESCAPE is pressed " << '\n';
                    return false;
                    break;
                default:
                    break;
                }
            }

            if (test_event.type == SDL_KEYUP)
            {
                switch (test_event.key.keysym.sym)
                {
                case SDLK_w:
                    std::cout << " W is released " << '\n';
                    break;
                case SDLK_s:
                    std::cout << " S is released " << '\n';
                    break;
                case SDLK_a:
                    std::cout << " A is released " << '\n';
                    break;
                case SDLK_d:
                    std::cout << " D is released " << '\n';
                    break;
                case SDLK_LCTRL:
                    std::cout << " BUTTON_ONE is released " << '\n';
                    break;
                case SDLK_SPACE:
                    std::cout << " BUTTON_TWO is released " << '\n';
                    break;
                case SDLK_RETURN:
                    std::cout << " START is released " << '\n';
                    break;
                default:
                    break;
                }
            }
        }
        return true;
    }

    //================ рисование треугольника =========================

    void render_triangle(const triangle& t)
    {

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), &t.v[0]);
        glEnableVertexAttribArray(0);
        glValidateProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    //================== переключение буферов ============================
    void swap_buffers()
    {
        SDL_GL_SwapWindow(window);
        glClearColor(0.3f, 0.3f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    //================== конструктор ===============================
    engine() { initialize(); }

    //================== деструктор ===============================
    ~engine() { SDL_Quit(); }
};
