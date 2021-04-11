/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Ncurses_color
*/

#include "Ncurses_disp_module.hpp"
#include "tools.hpp"

// TODO : func to find nearest color

static int find_nearest_color(int r, int g, int b)
{
    short red;
    short green;
    short blue;
    std::pair<int, int> nearest{-1, -1};
    int diff = 0;

    for (short i = 0; i < 8; i++) {
        color_content(i, &red, &green, &blue);
        diff = ABS((red - r)) + ABS((green - g)) + ABS((blue - b));
        if (nearest.first == -1 || nearest.second > diff) {
            nearest.first = i;
            nearest.second = diff;
        }
    }
    color_content(nearest.first, &red, &green, &blue);
    return nearest.first;
}

static int find_pair_arcade(short col1, short col2)
{
    short one;
    short two;

    for (int i = 0; i < COLOR_PAIRS; i++) {
        pair_content(i, &one, &two);
        if (col1 == one && col2 == two)
            return i;
    }
    return -1;
}

// TODO: func to search color
int find_color_pair(const color_t &col)
{
    int color_ch = find_nearest_color(col.ch_r, col.ch_g, col.ch_b);
    int color_bg = find_nearest_color(col.bg_r, col.bg_g, col.bg_b);
    int pair_to_ret = find_pair_arcade(color_ch, color_bg);

    return pair_to_ret;
}

// TODO: func to init pairs (to call in ctor)
void init_pairs_arcade()
{
    int i = 0;

    init_pair(i++, COLOR_BLACK, COLOR_BLACK);
    init_pair(i++, COLOR_BLACK, COLOR_RED);
    init_pair(i++, COLOR_BLACK, COLOR_GREEN);
    init_pair(i++, COLOR_BLACK, COLOR_YELLOW);
    init_pair(i++, COLOR_BLACK, COLOR_BLUE);
    init_pair(i++, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(i++, COLOR_BLACK, COLOR_CYAN);
    init_pair(i++, COLOR_BLACK, COLOR_WHITE);

    init_pair(i++, COLOR_RED, COLOR_BLACK);
    init_pair(i++, COLOR_RED, COLOR_RED);
    init_pair(i++, COLOR_RED, COLOR_GREEN);
    init_pair(i++, COLOR_RED, COLOR_YELLOW);
    init_pair(i++, COLOR_RED, COLOR_BLUE);
    init_pair(i++, COLOR_RED, COLOR_MAGENTA);
    init_pair(i++, COLOR_RED, COLOR_CYAN);
    init_pair(i++, COLOR_RED, COLOR_WHITE);

    init_pair(i++, COLOR_GREEN, COLOR_BLACK);
    init_pair(i++, COLOR_GREEN, COLOR_RED);
    init_pair(i++, COLOR_GREEN, COLOR_GREEN);
    init_pair(i++, COLOR_GREEN, COLOR_YELLOW);
    init_pair(i++, COLOR_GREEN, COLOR_BLUE);
    init_pair(i++, COLOR_GREEN, COLOR_MAGENTA);
    init_pair(i++, COLOR_GREEN, COLOR_CYAN);
    init_pair(i++, COLOR_GREEN, COLOR_WHITE);

    init_pair(i++, COLOR_YELLOW, COLOR_BLACK);
    init_pair(i++, COLOR_YELLOW, COLOR_RED);
    init_pair(i++, COLOR_YELLOW, COLOR_GREEN);
    init_pair(i++, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(i++, COLOR_YELLOW, COLOR_BLUE);
    init_pair(i++, COLOR_YELLOW, COLOR_MAGENTA);
    init_pair(i++, COLOR_YELLOW, COLOR_CYAN);
    init_pair(i++, COLOR_YELLOW, COLOR_WHITE);

    init_pair(i++, COLOR_BLUE, COLOR_BLACK);
    init_pair(i++, COLOR_BLUE, COLOR_RED);
    init_pair(i++, COLOR_BLUE, COLOR_GREEN);
    init_pair(i++, COLOR_BLUE, COLOR_YELLOW);
    init_pair(i++, COLOR_BLUE, COLOR_BLUE);
    init_pair(i++, COLOR_BLUE, COLOR_MAGENTA);
    init_pair(i++, COLOR_BLUE, COLOR_CYAN);
    init_pair(i++, COLOR_BLUE, COLOR_WHITE);

    init_pair(i++, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(i++, COLOR_MAGENTA, COLOR_RED);
    init_pair(i++, COLOR_MAGENTA, COLOR_GREEN);
    init_pair(i++, COLOR_MAGENTA, COLOR_YELLOW);
    init_pair(i++, COLOR_MAGENTA, COLOR_BLUE);
    init_pair(i++, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(i++, COLOR_MAGENTA, COLOR_CYAN);
    init_pair(i++, COLOR_MAGENTA, COLOR_WHITE);

    init_pair(i++, COLOR_CYAN, COLOR_BLACK);
    init_pair(i++, COLOR_CYAN, COLOR_RED);
    init_pair(i++, COLOR_CYAN, COLOR_GREEN);
    init_pair(i++, COLOR_CYAN, COLOR_YELLOW);
    init_pair(i++, COLOR_CYAN, COLOR_BLUE);
    init_pair(i++, COLOR_CYAN, COLOR_MAGENTA);
    init_pair(i++, COLOR_CYAN, COLOR_CYAN);
    init_pair(i++, COLOR_CYAN, COLOR_WHITE);

    init_pair(i++, COLOR_WHITE, COLOR_BLACK);
    init_pair(i++, COLOR_WHITE, COLOR_RED);
    init_pair(i++, COLOR_WHITE, COLOR_GREEN);
    init_pair(i++, COLOR_WHITE, COLOR_YELLOW);
    init_pair(i++, COLOR_WHITE, COLOR_BLUE);
    init_pair(i++, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(i++, COLOR_WHITE, COLOR_CYAN);
    init_pair(i++, COLOR_WHITE, COLOR_WHITE);
}