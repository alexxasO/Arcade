#include "SDL_disp_module.hpp"
#include "Ncurses_disp_module.hpp"
#include "Core.hpp"

int main(int ac, char **av)
{
    Ncurses_disp_module a;
    std::vector<cell_t> cell_vect;
    Core c(ac, av);
    cell_t line_blue = {false, 'l', 0x262df7, 0xFFFFFFFF, 0.0f, std::pair<int, int>(1, 1), std::pair<int, int>(1, 10), "", ""};
    cell_t rect_red = {false, 'r', 0xff6a34, 0xFFFFFFFF, 0.0f, std::pair<int, int>(20, 20), std::pair<int, int>(5, 5), "", ""};
    cell_t charac = {true, 'r', 0xff6a34, 0xFFFFFFFF, 0.0f, std::pair<int, int>(10, 10), std::pair<int, int>(5, 5), "", ""};
    cell_vect.push_back(line_blue);
    cell_vect.push_back(rect_red);
    cell_vect.push_back(charac);

    while (1) {
        if (!c.do_a_frame())
            break;
    }
    return 0;
}