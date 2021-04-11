/*
** EPITECH PROJECT, 2021
** Enemies.cpp
** File description:
** Enemies
*/

#ifndef ENEMIES_H_
#define ENEMIES_H_

#define BOARD_SIZE 40

#include <vector>
#include <memory>
#include "Cell.hpp"
#include "keys.hpp"
#include "IGameModule.hpp"
#include "Walls.hpp"
#include "Food.hpp"

namespace arcade::game
{
    class Enemies {
        public:
            Enemies(const int &);
            ~Enemies();

            // Member function
            void moveHorizontally(int, const std::vector<cell_t> &);
            void moveVertically(int, const std::vector<cell_t> &);
            bool move(const std::vector<cell_t> &);

            //setter
            void setTimer(const float &);

            cell_t _enemy;
        protected:
        private:
            key_t _key;
            float _timer;
    };
}

#endif /* !ENEMIES_H_ */
