/*
** EPITECH PROJECT, 2021
** SFML_disp_module.cpp
** File description:
** SFML_disp_module
*/

#ifndef SFML_disp_module_h
#define SFML_disp_module_h

#include "IDisplayModule.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

typedef void (*draw_form)(std::pair<int, int> x, std::pair<int, int> y, sf::RenderWindow &win, sf::Color color);
#define TILE_X 21
#define TILE_Y 10
#define DELTA_X(x) ((x) * TILE_X)
#define DELTA_Y(y) ((y) * TILE_Y)

class SFML_display_module : public IDisplayModule {
public:
    // Ctor & Dtor
    SFML_display_module();
    ~SFML_display_module() override;
    // Interfaces
    void interpretCells(std::vector<cell_t> &cells) override;
    void interpretSoloCell(const cell_t& cell);
    void createWindow(const std::string &name, int flags);
    std::vector<keys_e> pollEvent() override;
    void refreshScreen() override;
protected:
    std::vector<keys_e> _event;
    std::map<char, draw_form> _form_map;
    sf::RenderWindow _win;
    std::map<sf::Keyboard::Key, keys_e> _key_map = {
        {sf::Keyboard::LControl, CTRL},
        {sf::Keyboard::LShift, SHIFT_L},
        {sf::Keyboard::LAlt, ALT_L},
        {sf::Keyboard::LSystem, SUPER_L},
        {sf::Keyboard::RShift, SHIFT_R},
        {sf::Keyboard::RSystem, SUPER_R},
        {sf::Keyboard::Unknown, CAPS_LOCK},
        {sf::Keyboard::Escape, ESC},
        {sf::Keyboard::Tab, TAB},
        {sf::Keyboard::Space, SPACE},
        {sf::Keyboard::Return, RETURN},
        {sf::Keyboard::Backspace, BACKSPACE},
        {sf::Keyboard::Delete, DEL},
        {sf::Keyboard::Insert, INSERT},
        {sf::Keyboard::Home, HOME},
        {sf::Keyboard::End, END},
        {sf::Keyboard::PageUp, PAGE_UP},
        {sf::Keyboard::PageDown, PAGE_DOWN},
        {sf::Keyboard::Up, ARROW_UP},
        {sf::Keyboard::Down, ARROW_DOWN},
        {sf::Keyboard::Left, ARROW_LEFT},
        {sf::Keyboard::Right, ARROW_RIGHT},
        {sf::Keyboard::Num1, NUM_1},
        {sf::Keyboard::Num2, NUM_2},
        {sf::Keyboard::Num3, NUM_3},
        {sf::Keyboard::Num4, NUM_4},
        {sf::Keyboard::Num5, NUM_5},
        {sf::Keyboard::Num6, NUM_6},
        {sf::Keyboard::Num7, NUM_7},
        {sf::Keyboard::Num8, NUM_8},
        {sf::Keyboard::Num9, NUM_9},
        {sf::Keyboard::F1, F1},
        {sf::Keyboard::F2, F2},
        {sf::Keyboard::F3, F3},
        {sf::Keyboard::F4, F4},
        {sf::Keyboard::F5, F5},
        {sf::Keyboard::F6, F6},
        {sf::Keyboard::F7, F7},
        {sf::Keyboard::F8, F8},
        {sf::Keyboard::F9, F9},
        {sf::Keyboard::F10, F10},
        {sf::Keyboard::F11, F11},
        {sf::Keyboard::F12, F12},
        {sf::Keyboard::A, A},
        {sf::Keyboard::B, B},
        {sf::Keyboard::C, C},
        {sf::Keyboard::D, D},
        {sf::Keyboard::E, E},
        {sf::Keyboard::F, F},
        {sf::Keyboard::G, G},
        {sf::Keyboard::H, H},
        {sf::Keyboard::I, I},
        {sf::Keyboard::J, J},
        {sf::Keyboard::K, K},
        {sf::Keyboard::L, L},
        {sf::Keyboard::N, M},
        {sf::Keyboard::O, O},
        {sf::Keyboard::P, P},
        {sf::Keyboard::Q, Q},
        {sf::Keyboard::R, R},
        {sf::Keyboard::S, S},
        {sf::Keyboard::T, T},
        {sf::Keyboard::U, U},
        {sf::Keyboard::V, V},
        {sf::Keyboard::W, W},
        {sf::Keyboard::X, X},
        {sf::Keyboard::Y, Y},
        {sf::Keyboard::Z, Z},
        {sf::Keyboard::LBracket, BRACKET_LEFT},
        {sf::Keyboard::RBracket, BRACKET_RIGHT},
        {sf::Keyboard::SemiColon, SEMICOLON},
        {sf::Keyboard::Comma, COMMA},
        {sf::Keyboard::Period, PERIOD},
        {sf::Keyboard::Slash, SLASH},
        {sf::Keyboard::Backslash, BACKSLASH},
        {sf::Keyboard::Tilde, TILDE},
        {sf::Keyboard::Equal, EQUAL},
        {sf::Keyboard::Add, ADD},
        {sf::Keyboard::Subtract, SUBSTRACT},
        {sf::Keyboard::Multiply, MULTIPLY},
        {sf::Keyboard::Divide, DIVIDE},
        };
    private:
};

#endif /* !SFML_disp_module_h */
