/*
** EPITECH PROJECT, 2021
** Ncurses_disp_module.cpp
** File description:
** Ncurses_disp_module
*/

#ifndef Ncurses_disp_module_h
#define Ncurses_disp_module_h

#include <curses.h>
#include <vector>
#include "Cell.hpp"

class Ncurses_disp_module {
    public:
        Ncurses_disp_module();
        ~Ncurses_disp_module();

        void interpretCells(std::vector<cell_t> &cells);


    protected:
        WINDOW *main_win;

    private:
};

#endif /* !Ncurses_disp_module_h */
