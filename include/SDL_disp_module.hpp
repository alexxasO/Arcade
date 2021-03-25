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

class SDL_display_module : public IDisplayModule {
    public:
        // Ctor & Dtor
        SDL_display_module();
        ~SDL_display_module() override;
        // Interfaces
        void interpretCells(std::vector<cell_t> &cells) override;
        void createWindow(const std::string &name, int flags);
        void createRender(int flags);
        std::vector<keys_e> pollEvent() const override;
        void refreshScreen() override;
    protected:
        std::vector<keys_e> _event;
        SDL_Window *_win;
        SDL_Renderer  *_render;
    private:
};

#endif /* !SDL_display_module_h */
