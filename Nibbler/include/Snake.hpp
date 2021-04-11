/*
** EPITECH PROJECT, 2021
** Snake.cpp
** File description:
** Snake
*/

#ifndef Snake_h
#define Snake_h

#define BOARD_SIZE 40

#include "keys.hpp"

namespace arcade::game
{
    class Snake {
        public:
            Snake(const size_t &nb)
                : _size(nb), _Snake(nb), _key(ARROW_RIGHT)
            {
                std::pair<int, int> center(BOARD_SIZE / 2, BOARD_SIZE / 2);

                for (std::size_t i = 0; i != nb; i++) {
                    _Snake[i].position = {center.first - i, center.second};
                    _Snake[i].c = 'r';
                    _Snake[i].charColor = (!i ? 0xBE8AB088 : 0xBE8AB0FF);
                }
            };
            ~Snake() {};

            std::size_t _size;
            std::vector<cell_t> _Snake;
            keys_e _key;
        protected:
        private:
    };
}

#endif /* !Snake_h */
