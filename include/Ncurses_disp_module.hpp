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
#include <map>
#include "IDisplayModule.hpp"

typedef struct color
{
    int r;
    int g;
    int b;
    int a;
} color_t;


typedef void (*draw_func)(const cell_t &, const color_t &);

class Ncurses_disp_module : public IDisplayModule {
    public:
        Ncurses_disp_module();
        ~Ncurses_disp_module();

        void interpretCells(std::vector<cell_t> &cells) override;
        void interpret_cell(const cell_t &cell);
        virtual void refreshScreen() override;
        virtual std::vector<keys_e> pollEvent() override;

    protected:
        WINDOW *_main_win;
        std::map<char, draw_func> _form_map;

    private:
};

#endif /* !Ncurses_disp_module_h */
