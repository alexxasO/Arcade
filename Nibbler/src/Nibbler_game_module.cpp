/*
** EPITECH PROJECT, 2021
** Nibbler_game_module.cpp
** File description:
** Nibbler_game_module
*/

#include "Nibbler_game_module.hpp"

arcade::game::Nibbler_game_module::Nibbler_game_module()
    : _board(BOARD_SIZE * BOARD_SIZE), _score(0), _snake(4), _fruits(1)
{
}

arcade::game::Nibbler_game_module::~Nibbler_game_module()
{
}

// MEMBER FUNCTIONS

void arcade::game::Nibbler_game_module::update(std::vector<keys_e> &events)
{
    for (auto it = events.begin(); it != events.end(); it++) {
        if (*it == ARROW_DOWN)
            _snake._key = *it;
        else if (*it == ARROW_UP)
            _snake._key = *it;
        else if (*it == ARROW_LEFT)
            _snake._key = *it;
        else if (*it == ARROW_RIGHT)
            _snake._key = *it;
        if (*it == Q)
            fprintf(stderr, "You left the game\n");
        if (*it == M)
            fprintf(stderr, "Back to menu\n");
    }
    move();
    refreshBoard();
}

void arcade::game::Nibbler_game_module::refreshBoard()
{
    for (auto it = _board.begin(); it != _board.end(); it++) {
        it->c = ' ';
        for (auto jt = _fruits._apple.begin(); jt != _fruits._apple.end(); jt++) {
            if (jt->position == it->position)
                *it = *jt;
        }
        if (_snake._Snake.begin()->position == it->position) {
            if (it->c == 'o')
                eat();
            if (it->c == 'r')
                fprintf(stderr, "Game over\n");
        }
        for (auto jt = _snake._Snake.begin(); jt != _snake._Snake.end(); jt++) {
            if (jt->position == it->position)
                *it = *jt;
        }
    }
}

void arcade::game::Nibbler_game_module::reset()
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

const std::vector<arcade::cell_t> &arcade::game::Nibbler_game_module::getBoard()
{
    return _board;
}

int arcade::game::Nibbler_game_module::getScore()
{
    return _score;
}

// SETTERS

bool arcade::game::Nibbler_game_module::setBoard(const std::pair<int, int> &pos, const cell_t &cell)
{
    for (auto it = _board.begin(); it != _board.end(); it++)
        if (pos == it->position) {
            *it = cell;
            return true;
        }
    return false;
}

bool arcade::game::Nibbler_game_module::setScore(const int &score)
{
    if (_score - score < 0) {
        _score = 0;
        return false;
    }
    _score += score;
    return true;
}

// GAMEPLAY

void arcade::game::Nibbler_game_module::moveHorizontally(int dir)
{
    _lastPos = *_snake._Snake.end();
    for (auto it = _snake._Snake.end(); it != _snake._Snake.begin() - 1; it--) {
        it->position = {(it - 1)->position.first, (it - 1)->position.second + dir};
    }
    _snake._Snake.begin()->position.second + dir;
}

void arcade::game::Nibbler_game_module::moveVertically(int dir)
{
    _lastPos = *_snake._Snake.end();
    for (auto it = _snake._Snake.end(); it != _snake._Snake.begin() - 1; it--) {
        it->position = {(it - 1)->position.first + dir, (it - 1)->position.second};
    }
    _snake._Snake.begin()->position.first + dir;
}

bool arcade::game::Nibbler_game_module::move()
{
    if (_snake._key == ARROW_DOWN)
        moveVertically(1);
    else if (_snake._key == ARROW_UP)
        moveVertically(-1);
    else if (_snake._key == ARROW_LEFT)
        moveHorizontally(-1);
    else if (_snake._key == ARROW_RIGHT)
        moveHorizontally(1);
    if (_snake._Snake.begin()->position.first < 0 ||
        _snake._Snake.begin()->position.second < 0 ||
        _snake._Snake.begin()->position.first >= BOARD_SIZE ||
        _snake._Snake.begin()->position.second >= BOARD_SIZE) {
        fprintf(stderr, "Game over\n");
        return false;
    }
    return true;
}

void arcade::game::Nibbler_game_module::eat()
{
    setScore(_fruits._score);
    _snake._Snake.insert(_snake._Snake.end(), _lastPos);
    _fruits._apple.begin()->position = {rand() % BOARD_SIZE, rand() % BOARD_SIZE};
}
