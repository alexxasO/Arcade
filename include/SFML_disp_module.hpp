/*
** EPITECH PROJECT, 2021
** SFML_disp_module.cpp
** File description:
** SFML_disp_module
*/

#ifndef SFML_disp_module_h
#define SFML_disp_module_h

#include "IDisplayModule.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <deque>
#include <cmath>

class SFML_disp_module : public IDisplayModule  {
    public:
        SFML_disp_module();
        ~SFML_disp_module();

        void interpretCells(std::vector<cell_t> &cells);
        std::vector<keys_e> pollEvent();
        void refreshScreen();

    protected:
    private:
        sf::RenderWindow _window;
        sf::Event _event;
        std::string _map;
};

#endif /* !SFML_disp_module_h */
