#include "engine.hxx"

const std::string engine::system_name{"engine_sys"};

//====================================================================================
bool engine::initialize()
{
    if ((SDL_Init(SDL_INIT_EVERYTHING)) != 0)
    {
        const char* err_message = SDL_GetError();
        std::cerr << "error: failed call SDL_Init: " << err_message
                  << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Window* const window =
        SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 640, 480, ::SDL_WINDOW_OPENGL);

    if (window == nullptr)
    {
        std::cerr << "error: failed call SDL_CreateWindow: " << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    return true;
}

bool engine::initialize(const std::string& screen_mode_type, const int& in_width, const int& in_height)
{
    if (!(screen_mode_type == FULL_SCREEN) &&
        !(screen_mode_type == WINDOW_MODE))
    {
        std::cerr << "screen_mode_type  \n!!"
                  << "must be FULL_SCREEN or WINDOW_MODE\n";
        logger << "screen_mode_type must be FULL_SCREEN or WINDOW_MODE" << ERROR;
        return EXIT_FAILURE;
    }

    if ((SDL_Init(SDL_INIT_EVERYTHING)) != 0)
    {
        const char* err_message = SDL_GetError();
        std::cerr << "error: failed call SDL_Init: " << err_message
                  << std::endl;
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("Panzer Engine Demo", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height,
                              ::SDL_WINDOW_OPENGL);
    if (screen_mode_type == FULL_SCREEN)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }

    // SDL_ShowCursor(SDL_DISABLE);

    if (window == nullptr)
    {
        std::cerr << "error: failed call SDL_CreateWindow: " << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_assert(gl_context != nullptr);

    //    load_gl_func("glCreateShader", glCreateShader);
    //    load_gl_func("glShaderSource", glShaderSource);
    //    load_gl_func("glCompileShader", glCompileShader);
    //    load_gl_func("glGetShaderiv", glGetShaderiv);
    //    load_gl_func("glGetShaderInfoLog", glGetShaderInfoLog);
    //    load_gl_func("glDeleteShader", glDeleteShader);
    //    load_gl_func("glCreateProgram", glCreateProgram);
    //    load_gl_func("glAttachShader", glAttachShader);
    //    load_gl_func("glBindAttribLocation", glBindAttribLocation);
    //    load_gl_func("glLinkProgram", glLinkProgram);
    //    load_gl_func("glGetProgramiv", glGetProgramiv);
    //    load_gl_func("glGetProgramInfoLog", glGetProgramInfoLog);
    //    load_gl_func("glDeleteProgram", glDeleteProgram);
    //    load_gl_func("glUseProgram", glUseProgram);
    //    load_gl_func("glVertexAttribPointer", glVertexAttribPointer);
    //    load_gl_func("glEnableVertexAttribArray", glEnableVertexAttribArray);
    //    load_gl_func("glValidateProgram", glValidateProgram);
    //    load_gl_func("glGetUniformLocation", glGetUniformLocation);
    //    load_gl_func("glUniform1i", glUniform1i);
    //    load_gl_func("glActiveTexture", glActiveTexture_);
    //    load_gl_func("glUniform4fv", glUniform4fv);
    //    load_gl_func("glDisableVertexAttribArray", glDisableVertexAttribArray);

    //    old_create_shader();

    return true;
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

//====================================================================================
engine::engine() : logger(LogManager::get_logger(system_name))
{
    initialize();
}

//====================================================================================
engine::engine(const std::string& screen_mode_type,
               const int& in_width,
               const int& in_height) : logger(LogManager::get_logger(system_name)),
                                       width(in_width),
                                       height(in_height)
{
    initialize(screen_mode_type, width, height);
}

//====================================================================================
engine::~engine()
{
    SDL_Quit();
}
