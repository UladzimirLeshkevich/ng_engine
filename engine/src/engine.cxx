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

//====================================================================================
bool engine::events()
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
                logger << 102 << "W is released" << INFO;
                break;
            case SDLK_s:
                std::cout << " S is released " << '\n';
                logger << 104 << "S is released" << INFO;
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
