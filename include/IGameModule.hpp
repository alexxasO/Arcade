/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-arthur.jourdan
** File description:
** IGame
*/

/**
* @file IGameModule.hpp
* @brief Interface class for arcade games.
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include <vector>
#include <string>

#include "Cell.h"

class IGameModule {
    public:
        virtual ~IGameModule() = 0;

		virtual void update(std::vector<keys_e> &events) = 0;
        virtual void refreshBoard() = 0;
        virtual void reset() = 0;
        virtual std::vector<cell_t> getBoard() = 0;

		virtual int getScore() = 0;
		protected:
    private:
};

#endif /* !IGAMEMODULE_HPP_ */