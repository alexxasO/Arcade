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
    SDL_RenderDrawLine(render, DELTA_X(x.first), DELTA_Y(x.second), DELTA_X(y.first), DELTA_Y(y.second));
}

static void draw_rect(std::pair<int, int> x, std::pair<int, int> y, SDL_Renderer *render, SDL_Color color)
{
    SDL_Rect rect1;

    (void)y;
    rect1.x = DELTA_X(x.first);
    rect1.y = DELTA_Y(x.second);
    rect1.h = TILE_X;
    rect1.w = TILE_Y;

    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(render, &rect1);
}

static void draw_triangle(std::pair<int, int> x, std::pair<int, int> y, SDL_Renderer *render, SDL_Color color)
{
    (void)x;
    (void)y;
    (void)render;
    (void)color;
    //TODO: Implement triangle in SLD2
}

static void draw_circle(std::pair<int, int> x, std::pair<int, int> y, SDL_Renderer *render, SDL_Color color)
{
    int offset_x;
    int offset_y;
    int d;

    (void)y;
    offset_x = 0;
    offset_y = TILE_Y / 2;
    d = offset_y - 1;
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
    while (offset_y >= offset_x) {
        SDL_RenderDrawLine(render, DELTA_X(x.first) - offset_y, DELTA_Y(x.second) + offset_x,
                           DELTA_X(x.first) + offset_y, DELTA_Y(x.second) + offset_x);
        SDL_RenderDrawLine(render, DELTA_X(x.first) - offset_x, DELTA_Y(x.second) + offset_y,
                           DELTA_X(x.first) + offset_x, DELTA_Y(x.second) + offset_y);
        SDL_RenderDrawLine(render, DELTA_X(x.first) - offset_x, DELTA_Y(x.second) - offset_y,
                           DELTA_X(x.first) + offset_x, DELTA_Y(x.second) - offset_y);
        SDL_RenderDrawLine(render, DELTA_X(x.first) - offset_y, DELTA_Y(x.second) - offset_x,
                           DELTA_X(x.first) + offset_y, DELTA_Y(x.second) - offset_x);
        if (d >= 2 * offset_x) {
            d -= 2 * offset_x + 1;
            offset_x += 1;
        } else if (d < 2 * ((TILE_Y / 2) - offset_y)) {
            d += 2 * offset_y - 1;
            offset_y -= 1;
        } else {
            d += 2 * (offset_y - offset_x - 1);
            offset_y -= 1;
            offset_x += 1;
        }
    }
}

static void draw_text(const cell_t &cell, SDL_Renderer *render, SDL_Color color)
{
    TTF_Font *text = TTF_OpenFont("./my_assets/ostrich-regular.ttf", TILE_X);
    if (!text) {
        printf("ca a merde qql part %s\n", TTF_GetError());
        exit(84);
    }
    std::string mess(1, cell.c);
    SDL_Color White = {color.r, color.g, color.b, color.a};
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(text, mess.c_str(), White);
    SDL_Texture *Message = SDL_CreateTextureFromSurface(render, surfaceMessage);
    SDL_Rect Message_rect;

    Message_rect.x = DELTA_X(cell.position.first);
    Message_rect.y = DELTA_Y(cell.position.second);
    Message_rect.h = TILE_X;
    Message_rect.w = TILE_Y;
    SDL_RenderCopy(render, Message, nullptr, &Message_rect);
}

SDL_display_module::SDL_display_module()
{
    _win = nullptr;
    _render = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());
        exit(1);
    }
    if (TTF_Init() == -1) {
        printf("%s", TTF_GetError());

    }
    _form_map['r'] = &draw_rect;
    _form_map['l'] = &draw_line;
    _form_map['v'] = &draw_triangle;
    _form_map['o'] = &draw_circle;
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

    color.a = GETALPHA(cell.bgColor);
    color.r = GETRED(cell.bgColor);
    color.g = GETGREEN(cell.bgColor);
    color.b = GETBLUE(cell.bgColor);
    if (cell.plainChar) {
        draw_text(cell, _render, color);
        return;
    }
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