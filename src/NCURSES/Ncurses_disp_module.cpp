/*
** EPITECH PROJECT, 2021
** Ncurses_disp_module.cpp
** File description:
** Ncurses_disp_module
*/

#include "tools.hpp"
#include "Ncurses_disp_module.hpp"

static void place_char(char c, int x, int y, color_t &color)
{
    int col = find_color_pair(color);
    if (col < 0) {
        mvaddch(y, x, c);
        return;
    }
    attron(COLOR_PAIR(col));
    mvaddch(y, x, c);
    attroff(COLOR_PAIR(col));
}

static void draw_circle(const arcade::cell_t &cell, color_t &color)
{
    place_char('o', cell.position.first, cell.position.second, color);
}

static void draw_triangle(const arcade::cell_t &cell, color_t &color)
{
    place_char('v', cell.position.first, cell.position.second, color);
}

static void draw_line2(std::pair<int, int> coord, std::pair<int, int> coord2, color_t color)
{
    int x;
    int y;
    int dx = coord2.first - coord.first;
    int dy = coord2.second - coord.second;

    for (x = coord.first; x <= coord2.first; x++) {
        y = coord.second + dy * (x - coord.first) / dx;
        place_char('*', x, y, color);
    }
}

static void draw_line(const arcade::cell_t &cell, color_t &color)
{
    std::pair<int, int> x = cell.position;
    std::pair<int, int> y = cell.offset;

    if (x.second == x.first) {
        move(x.second, x.first);
        hline('*', (MAX(x.second, y.second) - MIN(x.second, y.second)));
    } else if (x.second == x.first) {
        move(x.second, y.second);
        vline('*', (MAX(x.first, y.first) - MIN(x.first, y.first)));
    } else
        draw_line2(x, y, color);
}

static void draw_char(const arcade::cell_t &cell, color_t &color)
{
    place_char(cell.c, cell.position.first, cell.position.second, color);
}

static void draw_rect(const arcade::cell_t &cell, color_t &color)
{
    place_char('#', cell.position.first, cell.position.second, color);
}

static void draw_space(const arcade::cell_t &cell, color_t &color)
{
    place_char(' ', cell.position.first, cell.position.second, color);
}

arcade::display::Ncurses_disp_module::Ncurses_disp_module()
{
    _main_win = initscr();
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support colors\n");
        exit(1);
    }
    start_color();
    init_pairs_arcade();
    nodelay(_main_win, TRUE);
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

    _nextColorID = 9;
    _nextPairID = 1;
    _form_map['r'] = &draw_rect;
    _form_map['l'] = &draw_line;
    _form_map['v'] = &draw_triangle;
    _form_map['o'] = &draw_circle;
    _form_map[' '] = &draw_space;
    _maxx = getmaxx(_main_win);
    _maxy = getmaxy(_main_win);
}

arcade::display::Ncurses_disp_module::~Ncurses_disp_module()
{
    endwin();
}

void arcade::display::Ncurses_disp_module::interpret_solo_cell(const cell_t &cell)
{
    color_t color{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    color.bg_a = GETALPHA(cell.bgColor) * 1000 / 255;
    color.ch_a = GETALPHA(cell.charColor) * 1000 / 255;
    color.bg_r = GETRED(cell.bgColor) * 1000 / 255;
    color.ch_r = GETRED(cell.charColor) * 1000 / 255;
    color.bg_g = GETGREEN(cell.bgColor) * 1000 / 255;
    color.ch_g = GETGREEN(cell.charColor) * 1000 / 255;
    color.bg_b = GETBLUE(cell.bgColor) * 1000 / 255;
    color.ch_b = GETBLUE(cell.charColor) * 1000 / 255;
    color.colID = _nextColorID;
    color.pairID = _nextPairID;

    if (!cell.plainChar) {
        if (_form_map[cell.c])
            _form_map[cell.c](cell, color);
        else
            draw_space(cell, color);
    } else {
        draw_char(cell, color);
    }
    _nextColorID = color.colID;
    _nextPairID = color.pairID;
}

void arcade::display::Ncurses_disp_module::interpretCells(const std::vector<cell_t> &cells)
{
    for (auto & cell : cells) {
        interpret_solo_cell(cell);
    }
}

void arcade::display::Ncurses_disp_module::refreshScreen()
{
    if (refresh() == ERR) {
        fprintf(stderr, "ncurses refresh error\n");
    }
}

std::vector<arcade::keys_e> arcade::display::Ncurses_disp_module::pollEvent()
{
    std::vector<keys_e> vec{};
    int ch = getch();

    if (ch) {
        if (ch == ERR) {
            return vec;
        }
        vec.push_back(_keymap[ch]);
    }

    return vec;
}

extern "C" {
    std::unique_ptr<arcade::display::IDisplayModule> entry_point()
    {
        return std::make_unique<arcade::display::Ncurses_disp_module>();
    }
}