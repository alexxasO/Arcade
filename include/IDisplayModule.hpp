/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-arthur.jourdan
** File description:
** ILibrary
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <vector>
#include <string>

#include "Cell.h"

class IDisplayModule {
    public:
        virtual ~IDisplayModule() = 0;

	    // Display board

        virtual void interpretCells(std::vector<cell_t> &cells) = 0;

        // Poll event

        virtual std::vector<keys_e> pollEvent() = 0;

        // Refresh frame

        virtual void refreshScreen() = 0;

    protected:
    private:
};

#endif /* !IDISPLAYMODULE_HPP_ */