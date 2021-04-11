/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Cell
*/

#ifndef CELL_T_
#define CELL_T_

#define SETRED(x, y) (x) = (((x) & ~(0xFF << 24)) | (((y) & 0xFF) << 24))
#define SETGREEN(x, y) (x) = (((x) & ~(0xFF << 16)) | (((y) & 0xFF) << 16))
#define SETBLUE(x, y) (x) = (((x) & ~(0xFF << 8)) | (((y) & 0xFF) << 8))
#define SETALPHA(x, y) (x) = (((x) & ~(0xFF << 0)) | (((y) & 0xFF) << 0))

#define GETRED(x) (((x) >> 24) & 0xFF)
#define GETGREEN(x) (((x) >> 16) & 0xFF)
#define GETBLUE(x) (((x) >> 8) & 0xFF)
#define GETALPHA(x) (((x) >> 0) & 0xFF)

#include <string>

namespace arcade
{
    typedef struct cell_s
    {
        bool plainChar{false};                      // to be displayed as a char
        char c{' '};                                // foam to display
        uint bgColor{0x000000FF};                   // RGBA
        uint charColor{0xFFFFFFFF};                 // RGBA
        float direction{0.0f};                      // degrees
        float size{1.0f};                           // size
        std::pair<int, int> position{0, 0};         // <x, y>
        std::pair<float, float> offset{0.5f, 0.5f}; // <x, y>
        std::string imagePath{};                    // data for image
        std::string soundPath{};                    // data for sound
    } cell_t;
} // namespace arcade

#endif /* !CELL_H_ */
