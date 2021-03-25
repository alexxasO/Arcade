#include "SDL_disp_module.hpp"

int main()
{
    SDL_display_module a;

    a.createWindow("test", 0);
    a.createRender(SDL_RENDERER_ACCELERATED);

    while (1) {
        a.draw(std::rand() % 255, std::rand() % 255, std::rand() % 255, 255);
        a.pollEvent();
        a.refreshScreen();
        SDL_Delay(16);
    }
    return 0;
}