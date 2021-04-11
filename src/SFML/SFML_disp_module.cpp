/*
** EPITECH PROJECT, 2021
** SFML_disp_module.cpp
** File description:
** SFML_disp_module
*/

#include "SFML_disp_module.hpp"

using namespace arcade::display;
using namespace arcade;

static void draw_line(const cell_t &cell, sf::RenderWindow &win, sf::Color color, sf::Color color_bg)
{
    (void)cell;
    (void)win;
    (void)color;
    (void)color_bg;
    //TODO: Draw line in SFML (rect with low width)
//    SDL_SetRenderDrawColor(win, color.r, color.g, color.b, color.a);
//    SDL_RenderDrawLine(win, DELTA_X(x.first), DELTA_Y(x.second), DELTA_X(y.first), DELTA_Y(y.second));

}

static void draw_rect(const cell_t &cell, sf::RenderWindow &win, sf::Color color, sf::Color color_bg)
{
    sf::RectangleShape rect1(sf::Vector2f(TILE_X, TILE_Y));

    (void)color_bg;
    rect1.setPosition((sf::Vector2f(DELTA_X(cell.position.first), DELTA_Y(cell.position.second))));
    rect1.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    win.draw(rect1);
}

static void draw_triangle(const cell_t &cell, sf::RenderWindow &win, sf::Color color, sf::Color color_bg)
{
    (void)cell;
    (void)color_bg;
    (void)win;
    (void)color;
    //TODO: Implement triangle in SLD2
}

static void draw_circle(const cell_t &cell, sf::RenderWindow &win, sf::Color color, sf::Color color_bg)
{
    sf::CircleShape circle((float)((TILE_X / 2) * cell.size));

    (void)cell;
    (void)color_bg;
    draw_rect(cell, win, color_bg, color);
    circle.setPosition(sf::Vector2f(DELTA_X((cell.position.first + cell.offset.first - 0.5)), DELTA_Y((cell.position.second + cell.offset.second - 0.5)) + (TILE_Y / 3)));
    circle.setFillColor(color);
    win.draw(circle);
}

static void draw_text(const cell_t &cell, sf::RenderWindow &win, sf::Color color)
{
    sf::Text text;
    sf::Font font;

    if (!font.loadFromFile("./assets/font/consolab.ttf")) {
        printf("ca a merde qql part %s\n", "font");
        exit(84);
    }
    text.setFont(font);
    text.setCharacterSize(TILE_Y);
    text.setString(std::string(1, cell.c));
    text.setFillColor(color);
    text.setPosition(sf::Vector2f(DELTA_X(cell.position.first), DELTA_Y(cell.position.second)));
    win.draw(text);
}

SFML_display_module::SFML_display_module()
{
    createWindow("Arcade", 1);
    _form_map['r'] = &draw_rect;
    _form_map['l'] = &draw_line;
    _form_map['v'] = &draw_triangle;
    _form_map['o'] = &draw_circle;
    _form_map[' '] = &draw_rect;
}

SFML_display_module::~SFML_display_module()
{
    if (_win.isOpen())
        _win.close();
}

void SFML_display_module::interpretSoloCell(const cell_t& cell)
{
    sf::Color color;
    sf::Color color_bg;

    color.a = GETALPHA(cell.charColor);
    color.r = GETRED(cell.charColor);
    color.g = GETGREEN(cell.charColor);
    color.b = GETBLUE(cell.charColor);
    color_bg.a = GETALPHA(cell.bgColor);
    color_bg.r = GETRED(cell.bgColor);
    color_bg.g = GETGREEN(cell.bgColor);
    color_bg.b = GETBLUE(cell.bgColor);
    if (cell.plainChar) {
        draw_text(cell, _win, color);
        return;
    }
    if (cell.c == ' ') {
        _form_map.at(cell.c)(cell, _win, color_bg, color);
        return;
    }
    try {
        _form_map.at(cell.c)(cell, _win, color, color_bg);
    } catch (const std::out_of_range& e){
    }
}

void SFML_display_module::interpretCells(const std::vector<cell_t> &cells)
{
    for (auto & cell : cells) {
        interpretSoloCell(cell);
    }
}

std::vector<keys_e> SFML_display_module::pollEvent()
{
    sf::Event ev{};

    _event.clear();
    while (_win.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed)
                _win.close();
        if (ev.type == sf::Event::KeyPressed) {
            if (_key_map[ev.key.code])
                _event.push_back(_key_map[ev.key.code]);
        }
    }
    return _event;
}

void SFML_display_module::refreshScreen()
{
    _win.display();
    _win.clear();
}

void SFML_display_module::createWindow(const std::string &name, int flags)
{
    (void)flags;
    _win.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), name);
}

extern "C" {
    std::unique_ptr<arcade::display::IDisplayModule> entry_point()
    {
        return std::make_unique<SFML_display_module>();
    }
}