#include "engine.hxx"

//==========================================================================
const std::string engine::system_name{"engine_sys"};

//==========================================================================
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
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
PFNGLUNIFORM1IPROC glUniform1i = nullptr;
PFNGLACTIVETEXTUREPROC glActiveTexture_ = nullptr;
PFNGLUNIFORM4FVPROC glUniform4fv = nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;

//====================================================================================
engine::engine() : logger(LogManager::get_logger(system_name))
{
    initialize();
}

//====================================================================================
engine::engine(const std::string& in_screen_mode_type,
               const int& in_width,
               const int& in_height) : logger(LogManager::get_logger(system_name)),
                                       width(in_width),
                                       height(in_height),
                                       screen_mode_type(in_screen_mode_type)
{
    logger->open_logfile("log.txt");

    if (!initialize(screen_mode_type, width, height))
    {
        std::cerr << "Application will be closed  \n!!";
        logger << "Engine is not initialized. Application will be closed" << SYSTEM_ERROR;
        logger->close_log();
        SDL_Quit();
        exit(1);
    }
}

//==========================================================================
bool engine::events()
{
    while (SDL_PollEvent(&test_event)) // TODO check with while and without while
    {
        if (test_event.type == SDL_QUIT)
        {
            logger << "window was closed by SDL_QUIT" << INFO;
            return false;
        }
        if (test_event.type == SDL_KEYDOWN)
        {
            switch (test_event.key.keysym.sym)
            {
            case (SDLK_w):
                key_W_flag = false;
                speed_to_up = 0.0f;
                break;
            case SDLK_s:
                key_S_flag = false;
                speed_to_down = 0.0f;
                break;
            case SDLK_a:
                key_A_flag = false;
                speed_to_left = 0.0f;
                break;
            case SDLK_d:
                key_D_flag = false;
                speed_to_right = 0.0f;
                break;
            case SDLK_LCTRL:
                key_LCTRL_flag = false;
                break;
            case SDLK_SPACE:
                key_SPACE_flag = false;
                break;
            case SDLK_RETURN:
                key_ENTER_flag = false;
                break;
            case SDLK_ESCAPE:
                key_Esc_flag = false;
                logger << "key ESCAPE was pressed" << INFO;
                return false;
            case (SDLK_q):
                key_Q_flag = false;
                break;
            case (SDLK_e):
                key_E_flag = false;
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
                key_W_flag = true;
                speed_to_up = speed_to_up_value;
                logger << "key W was pressed" << INFO;
                break;
            case SDLK_s:
                key_S_flag = true;
                speed_to_down = -speed_to_down_value;
                logger << "key S was pressed" << INFO;
                break;
            case SDLK_a:
                key_A_flag = true;
                speed_to_left = -speed_to_left_value;
                logger << "key A was pressed" << INFO;
                break;
            case SDLK_d:
                key_D_flag = true;
                speed_to_right = speed_to_right_value;
                logger << "key D was pressed" << INFO;
                break;
            case SDLK_LCTRL:
                key_LCTRL_flag = true;
                logger << "key LCTRL was pressed" << INFO;
                break;
            case SDLK_SPACE:
                key_SPACE_flag = true;
                logger << "key SPACE was pressed" << INFO;
                break;
            case SDLK_RETURN:
                key_ENTER_flag = true;
                logger << "key ENTER was pressed" << INFO;
                break;
            case (SDLK_q):
                key_Q_flag = true;
                logger << "key Q was pressed" << INFO;
                break;
            case (SDLK_e):
                key_E_flag = true;
                logger << "key E was pressed" << INFO;
                break;
            default:
                break;
            }
        }
        //===== mouse ====
        if (test_event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (test_event.button.button == SDL_BUTTON_LEFT)
            {
                int w = 0;
                int h = 0;
                SDL_GetWindowSize(window, &w, &h);

                key_MOUSE_flag = true;
                // pr_mouse_x_pos = mouse_x_pos;
                // pr_mouse_y_pos = mouse_y_pos;
                mouse_y_pos = test_event.button.y;
                mouse_x_pos = test_event.button.x;
                mouse_click = true;
            }
        }
        if (test_event.type == SDL_MOUSEBUTTONUP)
        {
            if (test_event.button.button == SDL_BUTTON_LEFT)
            {
                mouse_click = false;
            }
        }
    }
    return true;
}

//==========================================================================
void engine::render_triangle(const triangle& t)
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), &t.v[0]);
    glEnableVertexAttribArray(0);
    glValidateProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

//==========================================================================
void engine::swap_buffers()
{
    SDL_GL_SwapWindow(window);
    glClearColor(0.95f, 0.95f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//====================================================================================
engine::~engine()
{
    logger->close_log();
    SDL_Quit();
}

//====================================================================================
bool engine::initialize()
{
    if ((SDL_Init(SDL_INIT_EVERYTHING)) != 0)
    {
        const char* err_message = SDL_GetError();
        std::cerr << "error: failed call SDL_Init: " << err_message
                  << std::endl;
        return false;
    }

    SDL_Window* const window =
        SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 640, 480, ::SDL_WINDOW_OPENGL);

    if (window == nullptr)
    {
        std::cerr << "error: failed call SDL_CreateWindow: " << std::endl;
        SDL_Quit();
        return false;
    }

    return true;
}

//====================================================================================
bool engine::initialize(const std::string& screen_mode_type, const int& in_width, const int& in_height)
{
    if (screen_mode_type != FULL_SCREEN && screen_mode_type != WINDOW_MODE)
    {
        std::cerr << "screen_mode_type must be FULL_SCREEN or WINDOW_MODE\n";
        logger << "screen_mode_type must be FULL_SCREEN or WINDOW_MODE" << SYSTEM_ERROR;
        return false;
    }

    if ((SDL_Init(SDL_INIT_EVERYTHING)) != 0)
    {
        const char* err_message = SDL_GetError();
        std::cerr << "error: failed call SDL_Init: " << err_message << std::endl;
        logger << "Failed call SDL_Init(): " << err_message << SYSTEM_ERROR;
        return false;
    }

    window = SDL_CreateWindow("Engine Demo", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, in_width, in_height,
                              ::SDL_WINDOW_OPENGL);
    if (screen_mode_type == FULL_SCREEN)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }

    // SDL_ShowCursor(SDL_DISABLE);

    if (window == nullptr)
    {
        std::cerr << "error: failed call SDL_CreateWindow " << std::endl;
        logger << "Failed call SDL_CreateWindow" << ERROR;
        return false;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_assert(gl_context != nullptr);

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
    load_gl_func("glGetUniformLocation", glGetUniformLocation);
    load_gl_func("glUniform1i", glUniform1i);
    load_gl_func("glActiveTexture", glActiveTexture_);
    load_gl_func("glUniform4fv", glUniform4fv);
    load_gl_func("glDisableVertexAttribArray", glDisableVertexAttribArray);

    old_create_shader();

    logger << "Engine successful initialized with window " << in_width << "x" << in_height << " in " << screen_mode_type << INFO;
    return true;
}

//==========================================================================
template <typename T>
void engine::load_gl_func(const char* func_name, T& result)
{
    void* gl_pointer = SDL_GL_GetProcAddress(func_name);
    result = reinterpret_cast<T>(gl_pointer);
    if (nullptr == gl_pointer)
    {
        logger << "Can't load GL function" << func_name << SYSTEM_ERROR;
        throw std::runtime_error(std::string("can't load GL function") +
                                 func_name);
    }
    result = reinterpret_cast<T>(gl_pointer);
}

//==========================================================================
void engine::old_create_shader()
{
    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);

    std::string vertex_shader_src =
        "attribute vec2 a_position;"
        "attribute vec2 a_tex_coord;"
        "varying vec2 v_tex_coord;"
        "void         main()"
        "{v_tex_coord = a_tex_coord;"
        "gl_Position = vec4(a_position, 0.0, 1.0);}";

    const char* source = vertex_shader_src.data();
    glShaderSource(vert_shader, 1, &source, nullptr);

    glCompileShader(vert_shader);

    GLint compiled_status = 0;
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &compiled_status);

    if (compiled_status == 0)
    {
        std::cerr << "vertex shader compilation faild !!"
                  << "\n";
        logger << "Vertex shader compilation faild" << SYSTEM_ERROR;
        glDeleteShader(vert_shader);
    }

    // create fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragment_shader_src =
        "varying vec2 v_tex_coord;"
        "uniform sampler2D s_texture;"
        "void main()"
        "{gl_FragColor = texture2D(s_texture, v_tex_coord);}";
    source = fragment_shader_src.data();
    glShaderSource(fragment_shader, 1, &source, nullptr);

    glCompileShader(fragment_shader);

    compiled_status = 0;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compiled_status);

    if (compiled_status == 0)
    {
        std::cerr << "fragment shader compilation faild !!"
                  << "\n";
        logger << "Fragment shader compilation faild" << SYSTEM_ERROR;
        glDeleteShader(fragment_shader);
    }

    program = glCreateProgram();

    glAttachShader(program, vert_shader);
    glAttachShader(program, fragment_shader);

    glBindAttribLocation(program, 0, "a_position");
    glLinkProgram(program);
    glUseProgram(program);
    location = glGetUniformLocation(program, "s_texture");
    if (location < 0)
    {
        std::cerr << "uniform problem !!"
                  << "\n";
        logger << "Uniform problem" << SYSTEM_ERROR;
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
