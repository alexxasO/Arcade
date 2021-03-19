/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-killian.vallette [WSL: Ubuntu-20.04]
** File description:
** Cell
*/

#include <string>

typedef struct cell
{
    bool plainChar = false;
    char c = ' '; // foam to display
    uint bgColor = 0x000000FF; // RGBA
    uint charColor = 0xFFFFFFFF; // RGBA
    float direction = 0.0f; // degrees

    std::pair<int, int> position = {0, 0};
    std::pair<float, float> offset = {0.5f, 0.5f};
	std::string imagePath; // data for image
	std::string soundPath; // data for sound
} cell_t