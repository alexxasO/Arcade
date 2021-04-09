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

#include "Cell.hpp"
#include "keys.hpp"

namespace arcade {
namespace game
{
    class IGameModule {
      public:
        virtual ~IGameModule() = default;

        /**
         * @brief Update events and make one tick of the game
         *
         * @param events The events to be interpreted by the game
         *                in order to update it
         * @param elapsedTime The time in seconds elapsed since the last tick,
         *                if (0) : game in pause or not started
         */
        virtual void update(
            const std::vector<keys_e> &events, float elapsedTime) = 0;

        /**
         * @brief Reset the game and his board to default settings
         */
        virtual void reset() = 0;

        /**
         * @brief Get the board object representing the game
         *
         * @return A vector containing all the cells of the game board
         */
        virtual const std::vector<cell_t> &getBoard() const = 0;

        /**
         * @brief Get the Score object of the current game
         *
         * @return The actual score as an integer
         */
        virtual int getScore() const = 0;
    };
} // namespace game
} // namespace arcade

#endif /* !IGAMEMODULE_HPP_ */
