/*
** EPITECH PROJECT, 2021
** Ncurses_disp_module.cpp
** File description:
** Ncurses_disp_module
*/

#include "Ncurses_disp_module.hpp"
#include "tools.hpp"

static void draw_line(const cell_t &cell, const color_t &color)
{
    std::pair<int, int> x = cell.position;
    std::pair<int, int> y = cell.offset;

    if (x.second == y.second) {
        wmove(stdscr, x.second, x.first);
        hline('*', MAX(x.first, y.first) - MIN(x.first, y.first));
    }
    if (x.first == y.first) {
        wmove(stdscr, x.second, x.first);
        vline('*', MAX(x.second, y.second) - MIN(x.second, y.second));
    }
    // TODO: draw a non-straight line
}

static void draw_char(const cell_t &cell, const color_t &color)
{
    mvaddch(cell.position.second, cell.position.first, cell.c);
}

static void draw_rect(const cell_t &cell, const color_t &color)
{
    wmove(stdscr, cell.position.second, cell.position.first);
    hline('*', cell.offset.first);
    wmove(stdscr, cell.position.second, cell.position.first + (cell.offset.first - 1));
    vline('*', cell.offset.second);
    wmove(stdscr, cell.position.second + (cell.offset.second - 1), cell.position.first);
    hline('*', cell.offset.first);
    wmove(stdscr, cell.position.second, cell.position.first);
    vline('*', cell.offset.second);
}

Ncurses_disp_module::Ncurses_disp_module()
{
    _main_win = initscr();
    if (!_main_win)
        fprintf(stderr, "ncurses initscr error\n");
    if (cbreak() == ERR) {
        fprintf(stderr, "ncurses cbreak error\n");
    }
    if (noecho() == ERR) {
        fprintf(stderr, "ncurses noecho error\n");
    }
    if (keypad(stdscr, true) == ERR) {
        fprintf(stderr, "ncurses keypad error\n");
    }

    _form_map['r'] = &draw_rect;
    _form_map['l'] = &draw_line;
}

Ncurses_disp_module::~Ncurses_disp_module()
{
    endwin();
}

void Ncurses_disp_module::interpret_cell(const cell_t &cell)
{
    int posx = cell.position.first;
    int posy = cell.position.second;
    float dir = cell.direction;
    color_t color = {0, 0, 0, 0};

    color.a = GETALPHA(cell.bgColor);
    color.r = GETRED(cell.bgColor);
    color.g = GETGREEN(cell.bgColor);
    color.b = GETBLUE(cell.bgColor);

    if (!cell.plainChar) {
        _form_map[cell.c](cell, color);
    } else {
        mvaddch(posy, posx, cell.c);
    }
}

void Ncurses_disp_module::interpretCells(std::vector<cell_t> &cells)
{
    for (auto & cell : cells) {
        interpret_cell(cell);
    }
}

void Ncurses_disp_module::refreshScreen()
{
    if (refresh() == ERR) {
        fprintf(stderr, "ncurses refresh error\n");
    }
}

std::vector<keys_e> Ncurses_disp_module::pollEvent()
{
    std::vector<keys_e> vec = {UNKNOWN};

    return vec;
}
