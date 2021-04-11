/*
** EPITECH PROJECT, 2021
** Food.cpp
** File description:
** Food
*/

#ifndef FOOD_H_
#define FOOD_H_

#define BOARD_SIZE 40

#include <vector>
#include "Cell.hpp"

namespace arcade::game
{
    class Food {
        public:
            Food() : _picked(false), _powered(false)
            {
                _food = {
                    .c = 'o',
                    .charColor = 0xFFFF00FF,
                    .size = 0.3f
                };
            };
            ~Food() {};

            cell_t _food;
            bool _picked;
            bool _powered;
        protected:
        private:
    };
}

#endif /* !FOOD_H_ */
