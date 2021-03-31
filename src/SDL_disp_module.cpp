/*
** EPITECH PROJECT, 2021
** SDL_disp_module.cpp
** File description:
** SDL_disp_module
*/

#include "SDL_disp_module.hpp"

static void draw_line(std::pair<int, int> x, std::pair<int, int> y, SDL_Renderer *render, SDL_Color color)
{
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(render, DELTA(x.first), DELTA(x.second), DELTA(y.first), DELTA(y.second));
}

static void draw_rect(std::pair<int, int> x, std::pair<int, int> y, SDL_Renderer *render, SDL_Color color)
{
    SDL_Rect rect;

    rect.h = DELTA(y.first);
    rect.w = DELTA(y.second);
    rect.x = DELTA(x.first);
    rect.y = DELTA(x.second);
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(render, &rect);
}

SDL_display_module::SDL_display_module()
{
    _win = nullptr;
    _render = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());
        exit(1);
    }
    _form_map['r'] = &draw_rect;
    _form_map['l'] = &draw_line;
}

SDL_display_module::~SDL_display_module()
{
    if (_win)
        SDL_DestroyWindow(_win);
    SDL_Quit();
}

void SDL_display_module::interpretSoloCell(const cell_t& cell)
{
    SDL_Color color;

    if (cell.plainChar)
        return;
    color.a = GETALPHA(cell.bgColor);
    color.r = GETRED(cell.bgColor);
    color.g = GETGREEN(cell.bgColor);
    color.b = GETBLUE(cell.bgColor);
    _form_map[cell.c](cell.position, cell.offset, _render, color);

}

void SDL_display_module::interpretCells(std::vector<cell_t> &cells)
{
    for (auto & cell : cells) {
        interpretSoloCell(cell);
    }
}

std::vector<keys_e> SDL_display_module::pollEvent()
{
    SDL_Event ev;

    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
            case SDL_QUIT:
                std::exit(0);
            case SDLK_x:
                _event.push_back(X);
                break;
            default:
                return _event;
        }
    }
    return _event;
}

void SDL_display_module::refreshScreen()
{
    SDL_RenderPresent(_render);
}

void SDL_display_module::createWindow(const std::string &name, int flags)
{
    _win = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH, SCREEN_HEIGHT, flags);
    if (!_win) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }
}

void SDL_display_module::createRender(int flags)
{
    _render = SDL_CreateRenderer(_win, -1, flags);
    if (!_render) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void SDL_display_module::draw(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(_render, r, g, b, a);
    SDL_RenderClear(_render);
}