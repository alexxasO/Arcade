#include "SDL_disp_module.hpp"

int main()
{
    SDL_display_module a;
    std::vector<cell_t> cell_vect;

    cell_t line_blue = {false, 'l', 0x262df7, 0xFFFFFFFF, 0.0f, std::pair<int, int>(1, 1), std::pair<int, int>(3, 3), "", ""};
    cell_t rect_red = {false, 'r', 0xff6a34, 0xFFFFFFFF, 0.0f, std::pair<int, int>(10, 10), std::pair<int, int>(20, 20), "", ""};
    cell_t circle_green = {false, 'o', 0x33ff36, 0xFFFFFFFF, 0.0f, std::pair<int, int>(20, 20), std::pair<int, int>(20, 20), "", ""};
    cell_t text_c = {true, 'P', 0x33ff36, 0xFFFFFFFF, 0.0f, std::pair<int, int>(30, 30), std::pair<int, int>(20, 20), "", ""};
//    cell_vect.push_back(line_blue);
    cell_vect.push_back(rect_red);
    cell_vect.push_back(circle_green);
    cell_vect.push_back(text_c);
    a.createWindow("test", 0);
    a.createRender(SDL_RENDERER_ACCELERATED);

    while (1) {
        a.interpretCells(cell_vect);
        a.pollEvent();
        a.refreshScreen();
        SDL_Delay(16);
    }
    return 0;
}