/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Ncurses_color
*/

#include "Ncurses_disp_module.hpp"
#include "tools.hpp"

static int color_exists(const color_t &color, int isChar)
{
    short *actual_r = 0;
    short *actual_g = 0;
    short *actual_b = 0;
    short color_r = 0;
    short color_g = 0;
    short color_b = 0;

    if (isChar) {
        color_r = color.ch_r;
        color_g = color.ch_g;
        color_b = color.ch_b;
    } else {
        color_r = color.bg_r;
        color_g = color.bg_g;
        color_b = color.bg_b;
    }
    for (int i = 0; i <= 255; i++) {
        color_content(i, actual_r, actual_g, actual_b);
        if (ABS(*actual_r - color_r) <= 20 &&
            ABS(*actual_g - color_g) <= 20 &&
            ABS(*actual_b - color_b) <= 20) {
                return i;
        }
    }
    return -1;
}

int ncurses_init_new_color(color_t &color)
{
    int char_color = color.colID;
    int bg_color = color.colID + 1;
    if (char_color >= COLOR_PAIRS)
        return -1;
    fprintf(stderr, "char : %d, %d, %d\nbg : %d, %d, %d\nid : %d\n color exists : %d\n", color.ch_r, color.ch_g, color.ch_b, color.bg_r, color.bg_g, color.bg_b, char_color, color_exists(color, true));
    // TODO créer la/les couleur SI BESOIN, init la pair, renvoyez ID de la nouvelle pair
    // TODO: fetch color to see if it already exists
    int state = init_color(color.colID, color.ch_r, color.ch_g, color.ch_b);
    // TODO: check if state is successful return if not
    color.colID = color.colID + 1;
    state = init_color(color.colID, color.bg_r, color.bg_g, color.bg_b);
    // TODO: check if state is successful return if not
    color.colID = color.colID + 1;

    // TODO: create the color_pair
    state = init_pair(color.pairID, char_color, bg_color);
    // TODO: check if state is successful return if not
    color.pairID = color.pairID + 1;
    return color.pairID - 1;
}