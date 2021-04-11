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
#include <memory>
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

typedef void (*draw_func)(const arcade::cell_t &, color_t &);

namespace arcade::display {
    class Ncurses_disp_module : public IDisplayModule {
        public:
            Ncurses_disp_module();
            ~Ncurses_disp_module();

            void interpretCells(const std::vector<cell_t> &cells) override;
            void refreshScreen() override;
            std::vector<keys_e> pollEvent() override;

            void interpret_solo_cell(const cell_t &);

        protected:
            WINDOW *_main_win;
            std::map<char, draw_func> _form_map;
            int _maxx;
            int _maxy;
            int _nextColorID;
            int _nextPairID;

            std::map<int, keys_e> _keymap = {
                {'^', CTRL},
                {32, SHIFT_L},
                {'[', ALT_L},
                {KEY_HOME, SUPER_L},
                {32, SHIFT_R},
                {'[', ALT_R},
                {KEY_HOME, SUPER_R},
                // {, CAPS_LOCK},
                {27, ESC},
                {'\t', TAB},
                {' ', SPACE},
                {'\n', RETURN},
                {KEY_BACKSPACE, BACKSPACE},
                {127, DEL},
                {'?', INSERT},
                {KEY_HOME, HOME},
                {KEY_END, END},
                {KEY_PPAGE, PAGE_UP},
                {KEY_NPAGE, PAGE_DOWN},
                {KEY_UP, ARROW_UP},
                {KEY_DOWN, ARROW_DOWN},
                {KEY_LEFT, ARROW_LEFT},
                {KEY_RIGHT, ARROW_RIGHT},
                {'0', NUM_0},
                {'1', NUM_1},
                {'2', NUM_2},
                {'3', NUM_3},
                {'4', NUM_4},
                {'5', NUM_5},
                {'6', NUM_6},
                {'7', NUM_7},
                {'8', NUM_8},
                {'9', NUM_9},
                {KEY_F(1), F1},
                {KEY_F(2), F2},
                {KEY_F(3), F3},
                {KEY_F(4), F4},
                {KEY_F(5), F5},
                {KEY_F(6), F6},
                {KEY_F(7), F7},
                {KEY_F(8), F8},
                {KEY_F(9), F9},
                {KEY_F(10), F10},
                {KEY_F(11), F11},
                {KEY_F(12), F12},
                {'a', A},
                {'b', B},
                {'c', C},
                {'d', D},
                {'e', E},
                {'f', F},
                {'g', G},
                {'h', H},
                {'i', I},
                {'j', J},
                {'k', K},
                {'l', L},
                {'m', M},
                {'n', N},
                {'o', O},
                {'p', P},
                {'q', Q},
                {'r', R},
                {'s', S},
                {'t', T},
                {'u', U},
                {'v', V},
                {'w', W},
                {'x', X},
                {'y', Y},
                {'z', Z},
                {'[', BRACKET_LEFT},
                {']', BRACKET_RIGHT},
                {';', SEMICOLON},
                {',', COMMA},
                {':', PERIOD},
                {'\"', QUOTE},
                {'/', SLASH},
                {'\\', BACKSLASH},
                {'~', TILDE},
                {'=', EQUAL},
                {'+', ADD},
                {'-', SUBSTRACT},
                {'*', MULTIPLY},
                {'/', DIVIDE}
            };
    };
}

int find_color_pair(const color_t &col);
void init_pairs_arcade();

#endif /* !Ncurses_disp_module_h */
