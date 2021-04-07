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

typedef struct color_s
{
    short bg_r;
    short ch_r;
    short bg_g;
    short ch_g;
    short bg_b;
    short ch_b;
    short bg_a;
    short ch_a;
    int colID;
    int pairID;
} color_t;


typedef void (*draw_func)(const cell_t &, color_t &);

class Ncurses_disp_module : public IDisplayModule {
    public:
        Ncurses_disp_module();
        ~Ncurses_disp_module();

        void interpretCells(std::vector<cell_t> &) override;
        virtual void refreshScreen() override;
        virtual std::vector<keys_e> pollEvent() override;

        void interpret_cell(const cell_t &);

        // void draw_circle(const cell_t &, const color_t &);
        // void draw_rect(const cell_t &, const color_t &);
        // void draw_line(const cell_t &, const color_t &);
        // void draw_char(const cell_t &, const color_t &);

    protected:
        WINDOW *_main_win;
        std::map<char, draw_func> _form_map;
        int _maxx;
        int _maxy;
        int _nextColorID;
        int _nextPairID;

    private:
};

int ncurses_init_new_color(color_t &color);

#endif /* !Ncurses_disp_module_h */
