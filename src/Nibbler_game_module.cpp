/*
** EPITECH PROJECT, 2021
** Nibbler_game_module.cpp
** File description:
** Nibbler_game_module
*/

#include "Nibbler_game_module.hpp"

Nibbler_game_module::Nibbler_game_module()
    : _board(BOARD_SIZE * BOARD_SIZE), _score(0), _snake(4), _fruits(1)
{
}

Nibbler_game_module::~Nibbler_game_module()
{
}

// MEMBER FUNCTIONS

void Nibbler_game_module::update(std::vector<keys_e> &events)
{
    for (auto it = events.begin(); it != events.end(); it++) {
        if (*it == ARROW_DOWN)
            moveVertically(1);
        else if (*it == ARROW_UP)
            moveVertically(-1);
        else if (*it == ARROW_LEFT)
            moveHorizontally(-1);
        else if (*it == ARROW_RIGHT)
            moveHorizontally(1);
        else if (*it == Q)
            fprintf(stderr, "You left the game\n");
        else if (*it == M)
            fprintf(stderr, "Back to menu\n");
    }
}

void Nibbler_game_module::refreshBoard()
{
}

void Nibbler_game_module::reset()
{
    std::vector<cell_t> newBoard(BOARD_SIZE * BOARD_SIZE);
    Snake newSnake(4);
    Fruit newFruits(1);

    _score = 0;
    _board = newBoard;
    _snake = newSnake;
    _fruits = newFruits;
}

// GETTERS

const std::vector<cell_t> &Nibbler_game_module::getBoard()
{
    return _board;
}

int Nibbler_game_module::getScore()
{
    return _score;
}

// SETTERS

bool Nibbler_game_module::setBoard(const std::pair<int, int> &pos, const cell_t &cell)
{
    for (auto it = _board.begin(); it != _board.end(); it++)
        if (pos == it->position) {
            *it = cell;
            return true;
        }
    return false;
}

bool Nibbler_game_module::setScore(const int &score)
{
    if (_score - score < 0) {
        _score = 0;
        return false;
    }
    _score += score;
    return true;
}

// GAMEPLAY

bool Nibbler_game_module::moveHorizontally(int dir)
{
    for (auto it = _snake._Snake.end(); it != _snake._Snake.begin() - 1; it--) {
        it->position = {(it - 1)->position.first, (it - 1)->position.second + dir};
    }
    _snake._Snake.begin()->position.second + dir;
}

bool Nibbler_game_module::moveVertically(int dir)
{
    for (auto it = _snake._Snake.end(); it != _snake._Snake.begin() - 1; it--) {
        it->position = {(it - 1)->position.first + dir, (it - 1)->position.second};
    }
    _snake._Snake.begin()->position.first + dir;
}
