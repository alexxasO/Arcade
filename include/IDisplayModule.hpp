/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-arthur.jourdan
** File description:
** ILibrary
*/

/**
 * @file IDisplayModule.hpp
 * @brief Interface class for arcade games.
 */

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <vector>
#include <string>
#include <map>
#include "Cell.hpp"
#include "keys.hpp"
#include "define.hpp"

namespace arcade::display
{
    class IDisplayModule {
      public:
        virtual ~IDisplayModule() = default;

        /**
         * @brief Method which will interpret and print a board of cells
         *
         * @param cells The board of cells to interpret and print
         */
        virtual void interpretCells(const std::vector<cell_t> &cells) = 0;

        /**
         * @brief Method to get events caught b the current lib and his window
         *
         * @return The keys pressed since last call to pollEvent
         */
        virtual std::vector<keys_e> pollEvent() = 0;

        /**
         * @brief Call all necessary functions of the library used to refresh
         * the window
         */
        virtual void refreshScreen() = 0;
        protected:
        private:
        };
} // namespace arcade

#endif /* !IDISPLAYMODULE_HPP_ */
