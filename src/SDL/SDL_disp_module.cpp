/*
** EPITECH PROJECT, 2021
** SDL_disp_module.cpp
** File description:
** SDL_disp_module
*/

#include "SDL_disp_module.hpp"

using namespace arcade::display;
using namespace arcade;

static void draw_line(const cell_t &cell, SDL_Renderer *render, SDL_Color color, SDL_Color color_bg)
{
    (void)cell;
    (void)render;
    (void)color;
    (void)color_bg;
    //TODO: Draw line
//    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
//    SDL_RenderDrawLine(render, DELTA_X(x.first), DELTA_Y(x.second), DELTA_X(y.first), DELTA_Y(y.second));
}

static void draw_rect(const cell_t &cell, SDL_Renderer *render, SDL_Color color, SDL_Color color_bg)
{
    SDL_Rect rect1;

    (void)color_bg;
    rect1.x = DELTA_X(cell.position.first);
    rect1.y = DELTA_Y(cell.position.second);
    rect1.h = TILE_Y;
    rect1.w = TILE_X;

    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(render, &rect1);
}

static void draw_triangle(const cell_t &cell, SDL_Renderer *render, SDL_Color color, SDL_Color color_bg)
{
    draw_rect(cell, render, color, color_bg);
    //TODO: Implement triangle in SLD2
}

static void draw_circle(const cell_t &cell, SDL_Renderer *render, SDL_Color color, SDL_Color color_bg)
{
    int offset_x;
    int offset_y;
    int d;

    offset_x = 0;
    offset_y = (TILE_X / 2) * cell.size;
    d = offset_y - 1;
    draw_rect(cell, render, color_bg, color);
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
    while (offset_y >= offset_x) {
        SDL_RenderDrawLine(render, (DELTA_X((cell.position.first + cell.offset.first - 0.5)) + TILE_X / 2) - offset_y, (DELTA_Y((cell.position.second + cell.offset.second - 0.5))+ TILE_Y / 2) + offset_x,
                           (DELTA_X((cell.position.first + cell.offset.first - 0.5)) + TILE_X / 2) + offset_y, (DELTA_Y((cell.position.second + cell.offset.second - 0.5)) + TILE_Y / 2) + offset_x);
        SDL_RenderDrawLine(render, (DELTA_X((cell.position.first + cell.offset.first - 0.5)) + TILE_X / 2) - offset_x, (DELTA_Y((cell.position.second + cell.offset.second - 0.5)) + TILE_Y / 2) + offset_y,
                           (DELTA_X((cell.position.first + cell.offset.first - 0.5)) + TILE_X / 2) + offset_x, (DELTA_Y((cell.position.second + cell.offset.second - 0.5)) + TILE_Y / 2) + offset_y);
        SDL_RenderDrawLine(render, (DELTA_X((cell.position.first + cell.offset.first - 0.5)) + TILE_X / 2) - offset_x, (DELTA_Y((cell.position.second + cell.offset.second - 0.5)) + TILE_Y / 2) - offset_y,
                           (DELTA_X((cell.position.first + cell.offset.first - 0.5)) + TILE_X / 2) + offset_x, (DELTA_Y((cell.position.second + cell.offset.second - 0.5)) + TILE_Y / 2) - offset_y);
        SDL_RenderDrawLine(render, (DELTA_X((cell.position.first + cell.offset.first - 0.5)) + TILE_X / 2) - offset_y, (DELTA_Y((cell.position.second + cell.offset.second - 0.5)) + TILE_Y / 2) - offset_x,
                           (DELTA_X((cell.position.first + cell.offset.first - 0.5)) + TILE_X / 2) + offset_y, (DELTA_Y((cell.position.second + cell.offset.second - 0.5)) + TILE_Y / 2) - offset_x);
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

void SDL_display_module::draw_text(const cell_t &cell, SDL_Renderer *render, SDL_Color color, SDL_Color color_bg)
{
    std::string mess(1, cell.c);
    SDL_Color White = {color.r, color.g, color.b, color.a};
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(_font, mess.c_str(), White);
    SDL_Texture *Message = SDL_CreateTextureFromSurface(render, surfaceMessage);
    SDL_Rect Message_rect;

    draw_rect(cell, render, color_bg, SDL_Color());
    Message_rect.x = DELTA_X(cell.position.first);
    Message_rect.y = DELTA_Y(cell.position.second);
    Message_rect.h = TILE_Y;
    Message_rect.w = TILE_X;
    SDL_RenderCopy(render, Message, nullptr, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
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
    _font = TTF_OpenFont("./assets/font/consolab.ttf", TILE_Y);
    if (!_font) {
        printf("ca a merde qql part %s\n", TTF_GetError());
        exit(84);
    }
    _form_map['r'] = &draw_rect;
    _form_map['l'] = &draw_line;
    _form_map['v'] = &draw_triangle;
    _form_map['o'] = &draw_circle;
    _form_map[' '] = &draw_rect;
    createWindow("Arcade", 0);
    createRender(SDL_RENDERER_ACCELERATED);
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
    SDL_Color color_bg;

    color.a = GETALPHA(cell.charColor);
    color.r = GETRED(cell.charColor);
    color.g = GETGREEN(cell.charColor);
    color.b = GETBLUE(cell.charColor);
    color_bg.a = GETALPHA(cell.bgColor);
    color_bg.r = GETRED(cell.bgColor);
    color_bg.g = GETGREEN(cell.bgColor);
    color_bg.b = GETBLUE(cell.bgColor);
    if (cell.plainChar) {
        draw_text(cell, _render, color, color_bg);
        return;
    }
    if (cell.c == ' ') {
        _form_map.at(cell.c)(cell, _render, color_bg, color);
        return;
    }
    try {
        _form_map.at(cell.c)(cell, _render, color, color_bg);
    }
    catch (const std::out_of_range& e){}
}

void SDL_display_module::interpretCells(const std::vector<cell_t> &cells)
{
    for (auto & cell : cells) {
        interpretSoloCell(cell);
    }
}

std::vector<keys_e> SDL_display_module::pollEvent()
{
    SDL_Event ev;

    _event.clear();
    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT)
            std::exit(0);
        if (ev.type == SDL_KEYDOWN) {
            if (_key_map[ev.key.keysym.sym])
                _event.push_back(_key_map[ev.key.keysym.sym]);
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

extern "C" {

std::unique_ptr<IDisplayModule> entry_point()
{
    return std::make_unique<SDL_display_module>();
}
}