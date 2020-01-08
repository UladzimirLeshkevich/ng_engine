#include "game.hxx"
#include "engine.hxx"

#include <iostream>

int main(int /*argc*/, char* /*argv*/[])
{
    std::cout << "!!!!!!!!!!!!!!!!!!!" << std::endl;
    engine obj;

    bool loop = true;

    while (loop)
    {
        loop = obj.events();
    }

    return EXIT_SUCCESS;
}
