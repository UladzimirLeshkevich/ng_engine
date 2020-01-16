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

//==========================================================================
bool engine::events()
{

    SDL_PollEvent(&test_event);

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
            //speed_to_up = speed_to_up_value;
            speed_to_up = 0.0f;
            break;
        case SDLK_s:
            key_S_flag = false;
            speed_to_down = 0.0f;
            //speed_to_down = -speed_to_down_value;
            break;
        case SDLK_a:
            key_A_flag = false;
            speed_to_left = 0.0f;
            //speed_to_left = -speed_to_left_value;
            break;
        case SDLK_d:
            key_D_flag = false;
            //speed_to_right = speed_to_right_value;
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
            //speed_to_up = 0.0f;
            break;
        case SDLK_s:
            key_S_flag = true;
            speed_to_down = -speed_to_down_value;
            logger << "key S was pressed" << INFO;
            //speed_to_down = 0.0f;
            break;
        case SDLK_a:
            key_A_flag = true;
            speed_to_left = -speed_to_left_value;
            logger << "key A was pressed" << INFO;
            //speed_to_left = 0.0f;
            break;
        case SDLK_d:
            key_D_flag = true;
            speed_to_right = speed_to_right_value;
            logger << "key D was pressed" << INFO;
            //speed_to_right = 0.0f;
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

    return true;
}

//====================================================================================
engine::engine() : logger(LogManager::get_logger(system_name))
{
    initialize();
}

//====================================================================================
engine::~engine()
{
    SDL_Quit();
}
