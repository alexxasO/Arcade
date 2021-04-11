/*
** EPITECH PROJECT, 2021
** Pacman.cpp
** File description:
** Pacman
*/

#ifndef PACMAN_H_
#define PACMAN_H_

#define BOARD_SIZE 40

#include <vector>
#include <memory>
#include "Cell.hpp"
#include "keys.hpp"
#include "IGameModule.hpp"
#include "Walls.hpp"
#include "Food.hpp"
#include "Enemies.hpp"

namespace arcade::game
{
    class Pacman : public arcade::game::IGameModule {
        public:
            Pacman();
            ~Pacman();

            /* Member functions */
            void update(const std::vector<keys_e> &, float);
            void refreshBoard();
            void reset();
            void initBoard();
            void setTextOnBoard(std::pair<int, int>, std::string);

            /* Gameplay */
            void moveHorizontally(int);
            void moveVertically(int);
            bool move();
            void eat();
            bool checkBody();

            /* Getters */
            const std::vector<cell_t> &getBoard() const;
    		int getScore() const;

            /* Setters */
            bool setBoard(const std::pair<int, int> &, const cell_t &);
    		bool setScore(const int &);

        protected:
        private:
            std::vector<cell_t> _board;
            int _score;
            float _timer;
            cell_t _pacman;
            key_t _key;
            Walls _walls;
            std::vector<Food> _food;
            bool _smooth;
            std::vector<Enemies> _enemies;
    };
}

#endif /* !PACMAN_H_ */
