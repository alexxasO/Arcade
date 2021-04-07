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
    sf::RenderWindow _win;;
private:
};

#endif /* !SFML_disp_module_h */
