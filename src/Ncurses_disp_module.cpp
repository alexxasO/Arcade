/*
** EPITECH PROJECT, 2021
** Ncurses_disp_module.cpp
** File description:
** Ncurses_disp_module
*/

#include "Ncurses_disp_module.hpp"

Ncurses_disp_module::Ncurses_disp_module()
{
    main_win = initscr();
    if (cbreak() == ERR) {
        fprintf(stderr, "ncurses cbreak error\n");
    }
    if (noecho() == ERR) {
        fprintf(stderr, "ncurses noecho error\n");
    }
    if (keypad(stdscr, true) == ERR) {
        fprintf(stderr, "ncurses keypad error\n");
    }
}

Ncurses_disp_module::~Ncurses_disp_module()
{
    endwin();
}

void interpretCells(std::vector<cell_t> &cells)
{

}
