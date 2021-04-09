/*
** EPITECH PROJECT, 2021
** SFML_disp_module.cpp
** File description:
** SFML_disp_module
*/

#include "SFML_disp_module.hpp"

using namespace arcade::display;
using namespace arcade;

static void draw_line(std::pair<int, int> x, std::pair<int, int> y, sf::RenderWindow &win, sf::Color color)
{
    (void)x;
    (void)y;
    (void)win;
    (void)color;
    //TODO: Draw line in SFML (rect with low width)
//    SDL_SetRenderDrawColor(win, color.r, color.g, color.b, color.a);
//    SDL_RenderDrawLine(win, DELTA_X(x.first), DELTA_Y(x.second), DELTA_X(y.first), DELTA_Y(y.second));

}

static void draw_rect(std::pair<int, int> x, std::pair<int, int> y, sf::RenderWindow &win, sf::Color color)
{
    sf::RectangleShape rect1(sf::Vector2f(TILE_X, TILE_Y));

    (void)y;
    rect1.setPosition((sf::Vector2f(DELTA_X(x.first), DELTA_Y(x.second))));
    rect1.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    win.draw(rect1);
}

static void draw_triangle(std::pair<int, int> x, std::pair<int, int> y, sf::RenderWindow &win, sf::Color color)
{
    (void)x;
    (void)y;
    (void)win;
    (void)color;
    //TODO: Implement triangle in SLD2
}

static void draw_circle(std::pair<int, int> x, std::pair<int, int> y, sf::RenderWindow &win, sf::Color color)
{
    sf::CircleShape circle((float)TILE_Y / 2);

    (void)y;
    circle.setPosition(sf::Vector2f(DELTA_X(x.first), DELTA_Y(x.second)));
    circle.setFillColor(color);
    win.draw(circle);
}

static void draw_text(const cell_t &cell, sf::RenderWindow &win, sf::Color color)
{
    sf::Text text;
    sf::Font font;

    if (!font.loadFromFile("./my_assets/ostrich-regular.ttf")) {
        printf("ca a merde qql part %s\n", "font");
        exit(84);
    }
    text.setFont(font);
    text.setCharacterSize(TILE_X);
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
    std::cout << "SFML ctor" << std::endl;
}

SFML_display_module::~SFML_display_module()
{
    if (_win.isOpen())
        _win.close();
}

void SFML_display_module::interpretSoloCell(const cell_t& cell)
{
    sf::Color color;

    color.a = GETALPHA(cell.charColor);
    color.r = GETRED(cell.charColor);
    color.g = GETGREEN(cell.charColor);
    color.b = GETBLUE(cell.charColor);
    if (cell.plainChar) {
        draw_text(cell, _win, color);
        return;
    }
    _form_map.at(cell.c)(cell.position, cell.offset, _win, color);

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

std::unique_ptr<IDisplayModule> entry_point()
{
    return std::make_unique<SFML_display_module>();
}
}