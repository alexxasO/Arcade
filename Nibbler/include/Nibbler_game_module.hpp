/*
** EPITECH PROJECT, 2021
** Nibbler_game_module.cpp
** File description:
** Nibbler_game_module
*/

#ifndef Nibbler_game_module_h
#define Nibbler_game_module_h

#define BOARD_SIZE 40

#include <vector>
#include "Cell.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"
#include "IGameModule.hpp"

class Nibbler_game_module : public game::IGameModule {
    public:
        Nibbler_game_module();
        ~Nibbler_game_module();

        /* Member functions */
		void update(std::vector<keys_e> &events);
        void refreshBoard();
        void reset();

        /* Gameplay */
        bool moveHorizontally(int dir);
        bool moveVertically(int dir);
        bool move();
        void eat();

        /* Getters */
        const std::vector<cell_t> &getBoard();
		int getScore();

        /* Setters */
        bool setBoard(const std::pair<int, int> &, const cell_t &);
		bool setScore(const int &);

    protected:
    private:
        std::vector<cell_t> _board;
        int _score;
        Snake _snake;
        Fruit _fruits;
        cell_t _lastPos;
};

#endif /* !Nibbler_game_module_h */
