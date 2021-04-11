/*
** EPITECH PROJECT, 2021
** SDL_disp_module.cpp
** File description:
** SDL_disp_module
*/

#ifndef SDL_display_module_h
#define SDL_display_module_h

#include "IDisplayModule.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <string>
#include <iostream>

typedef void (*draw_form_sdl)(const arcade::cell_t &cell, SDL_Renderer *render, SDL_Color color, SDL_Color color_bg);
#define TILE_X 10
#define TILE_Y 21
#define DELTA_X(x) ((x) * TILE_X)
#define DELTA_Y(y) ((y) * TILE_Y)

namespace arcade { namespace display {
        std::unique_ptr<IDisplayModule> entry_point();
class SDL_display_module : public IDisplayModule {
public:
    // Ctor & Dtor
    SDL_display_module();

    ~SDL_display_module() override;

    // Interfaces
    void interpretCells(const std::vector<cell_t> &cells) override;

    void interpretSoloCell(const cell_t &cell);

    void createWindow(const std::string &name, int flags);

    void createRender(int flags);

    std::vector<keys_e> pollEvent() override;

    void refreshScreen() override;

    void draw_text(const cell_t &cell, SDL_Renderer *render, SDL_Color color, SDL_Color color_bg);

protected:
    std::vector<keys_e> _event;
    std::map<char, draw_form_sdl> _form_map;
    SDL_Window *_win;
    SDL_Renderer *_render;
    TTF_Font *_font;
    std::map<SDL_Keycode, keys_e> _key_map = {
            {SDLK_LCTRL,        CTRL},
            {SDLK_LSHIFT,       SHIFT_L},
            {SDLK_LALT,         ALT_L},
            {SDLK_LGUI,         SUPER_L},
            {SDLK_RSHIFT,       SHIFT_R},
            {SDLK_RALT,         ALT_R},
            {SDLK_RGUI,         SUPER_R},
            {SDLK_CAPSLOCK,     CAPS_LOCK},
            {SDLK_ESCAPE,       ESC},
            {SDLK_TAB,          TAB},
            {SDLK_SPACE,        SPACE},
            {SDLK_RETURN,       RETURN},
            {SDLK_BACKSPACE,    BACKSPACE},
            {SDLK_DELETE,       DEL},
            {SDLK_INSERT,       INSERT},
            {SDLK_HOME,         HOME},
            {SDLK_END,          END},
            {SDLK_PAGEUP,       PAGE_UP},
            {SDLK_PAGEDOWN,     PAGE_DOWN},
            {SDLK_UP,           ARROW_UP},
            {SDLK_DOWN,         ARROW_DOWN},
            {SDLK_LEFT,         ARROW_LEFT},
            {SDLK_RIGHT,        ARROW_RIGHT},
            {SDLK_RIGHT,        ARROW_RIGHT},
            {SDLK_0,            NUM_0},
            {SDLK_1,            NUM_1},
            {SDLK_2,            NUM_2},
            {SDLK_3,            NUM_3},
            {SDLK_4,            NUM_4},
            {SDLK_5,            NUM_5},
            {SDLK_6,            NUM_6},
            {SDLK_7,            NUM_7},
            {SDLK_8,            NUM_8},
            {SDLK_9,            NUM_9},
            {SDLK_F1,           F1},
            {SDLK_F2,           F2},
            {SDLK_F3,           F3},
            {SDLK_F4,           F4},
            {SDLK_F5,           F5},
            {SDLK_F6,           F6},
            {SDLK_F7,           F7},
            {SDLK_F8,           F8},
            {SDLK_F9,           F9},
            {SDLK_F10,          F10},
            {SDLK_F11,          F11},
            {SDLK_F12,          F12},
            {SDLK_a,            A},
            {SDLK_b,            B},
            {SDLK_c,            C},
            {SDLK_d,            D},
            {SDLK_e,            E},
            {SDLK_f,            F},
            {SDLK_g,            G},
            {SDLK_h,            H},
            {SDLK_i,            I},
            {SDLK_j,            J},
            {SDLK_k,            K},
            {SDLK_l,            L},
            {SDLK_m,            M},
            {SDLK_n,            N},
            {SDLK_o,            O},
            {SDLK_p,            P},
            {SDLK_q,            Q},
            {SDLK_r,            R},
            {SDLK_s,            S},
            {SDLK_t,            T},
            {SDLK_u,            U},
            {SDLK_v,            V},
            {SDLK_w,            W},
            {SDLK_x,            X},
            {SDLK_y,            Y},
            {SDLK_z,            Z},
            {SDLK_LEFTBRACKET,  BRACKET_LEFT},
            {SDLK_RIGHTBRACKET, BRACKET_RIGHT},
            {SDLK_SEMICOLON,    SEMICOLON},
            {SDLK_COMMA,        COMMA},
            {SDLK_PERIOD,       PERIOD},
            {SDLK_QUOTE,        QUOTE},
            {SDLK_SLASH,        SLASH},
            {SDLK_BACKSLASH,    BACKSLASH},
            {SDLK_BACKQUOTE,    TILDE},
            {SDLK_EQUALS,       EQUAL},
            {SDLK_PLUS,         ADD},
            {SDLK_MINUS,        SUBSTRACT},
            {SDLK_ASTERISK,     MULTIPLY},
            {SDLK_SLASH,        DIVIDE},
    };
private:
};
}
}
#endif /* !SDL_display_module_h */
