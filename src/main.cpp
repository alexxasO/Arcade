/*
** EPITECH PROJECT, 2021
** arcade-B-400
** File description:
** main
*/

// #include "SDL_disp_module.hpp"

// int main()
// {
//     SDL_display_module a;
//     std::vector<cell_t> cell_vect;

//     cell_t line_blue = {false, 'l', 0x262df7, 0xFFFFFFFF, 0.0f, std::pair<int, int>(1, 1), std::pair<int, int>(3, 3), "", ""};
//     cell_t rect_red = {false, 'r', 0xff6a34, 0xFFFFFFFF, 0.0f, std::pair<int, int>(2, 2), std::pair<int, int>(4, 4), "", ""};
//     cell_vect.push_back(line_blue);
//     cell_vect.push_back(rect_red);
//     a.createWindow("test", 0);
//     a.createRender(SDL_RENDERER_ACCELERATED);

//     while (1) {
//         a.interpretCells(cell_vect);
//         a.pollEvent();
//         a.refreshScreen();
//         SDL_Delay(16);
//     }
//     return 0;
// }

#include <string>
#include <iostream>
#include <filesystem>
#include <map>

int main(void)
{
    std::string path = "./lib";
    std::map<std::string, bool> map;
    std::size_t pos;
    std::string temp;

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        temp = (entry.path().c_str() + 6);
        pos = temp.find(".so");
        map[temp.erase(pos, 3)] = false;
    }
    for (auto it = map.begin(); it != map.end(); it++)
    {
        std::cout << it->first << std::endl;
    }

    return 0;
}
