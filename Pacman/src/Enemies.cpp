/*
** EPITECH PROJECT, 2021
** Enemies.cpp
** File description:
** Enemies
*/

#include "Enemies.hpp"

arcade::game::Enemies::Enemies(const int &nb)
    : _timer(0)
{
    _key = ((!nb) ? ARROW_RIGHT : ((nb == 1) ?
        ARROW_LEFT : ((nb == 2) ? ARROW_DOWN : ARROW_UP)));
    uint color = ((!nb) ? 0xFF00FFFF : ((nb == 1) ?
        0xFF0000FF : ((nb == 2) ? 0x00FFFFFF : 0x00FF00FF)));
    std::pair<int, int> pos = ((!nb) ? (std::pair<int, int>){20, 20} : ((nb == 1) ?
        (std::pair<int, int>){21, 21} : ((nb == 2) ? (std::pair<int, int>){19, 19} :
        (std::pair<int, int>){18, 18})));

    _enemy = {
        .c = 'o',
        .charColor = color,
        .position = pos
    };
}

arcade::game::Enemies::~Enemies()
{
}

// MEMBER FUNCTIONS

// GETTERS

// SETTERS

// GAMEPLAY

void arcade::game::Enemies::moveHorizontally(int dir, const std::vector<cell_t> &board)
{
    std::pair<int, int> newPos = _enemy.position;

    newPos.first += dir;
    for (std::size_t i = 0; i < (BOARD_SIZE * BOARD_SIZE); i++) {
        if (board[i].position == newPos && board[i].c == 'r')
            return;
    }
    _enemy.position.first += dir;
    if (_enemy.position.first < 0)
        _enemy.position.first = BOARD_SIZE;
    else if (_enemy.position.first >= BOARD_SIZE)
        _enemy.position.first = (-1);

}

void arcade::game::Enemies::moveVertically(int dir, const std::vector<cell_t> &board)
{
    std::pair<int, int> newPos = _enemy.position;

    newPos.second += dir;
    for (std::size_t i = 0; i < (BOARD_SIZE * BOARD_SIZE); i++) {
        if (board[i].position == newPos && board[i].c == 'r')
            return;
    }
    _enemy.position.second += dir;
    if (_enemy.position.second < 0)
        _enemy.position.second = BOARD_SIZE;
    else if (_enemy.position.second >= BOARD_SIZE)
        _enemy.position.second = (-1);
}

bool arcade::game::Enemies::move(const std::vector<cell_t> &board)
{
    int rd = rand() % 4;

    if (_timer <= 10)
        return false;
    if (_key == ARROW_DOWN)
        moveVertically(1, board);
    else if (_key == ARROW_UP)
        moveVertically(-1, board);
    else if (_key == ARROW_LEFT)
        moveHorizontally(-1, board);
    else if (_key == ARROW_RIGHT)
        moveHorizontally(1, board);
    if ((int)_timer % (rand() % 6 + 1) <= 0.5)
        _key = ((!rd) ? ARROW_RIGHT : ((rd == 1) ?
        ARROW_LEFT : ((rd == 2) ? ARROW_DOWN : ARROW_UP)));
    return true;
}

void arcade::game::Enemies::setTimer(const float &timer)
{
    _timer += timer;
}
