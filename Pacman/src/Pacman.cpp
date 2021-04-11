/*
** EPITECH PROJECT, 2021
** Pacman.cpp
** File description:
** Pacman
*/

#include "Pacman.hpp"

arcade::game::Pacman::Pacman()
    : _board(BOARD_SIZE * BOARD_SIZE), _score(0), _timer(0), _key(ARROW_UP)
{
    fprintf(stderr, "test0\n");
    _pacman = {
        .c = 'o',
        .charColor = 0x00FF00FF,
        .position = {BOARD_SIZE / 2, BOARD_SIZE / 2}
    };
    initBoard();
}

arcade::game::Pacman::~Pacman()
{
}

// MEMBER FUNCTIONS

void arcade::game::Pacman::initBoard()
{
    fprintf(stderr, "test1\n");
    _board = _walls._walls;
    fprintf(stderr, "test2\n");
    setTextOnBoard({1, 1}, "PACMAN");
    setTextOnBoard({12, 1}, "Score : " + std::to_string(_score));
}

void arcade::game::Pacman::update(const std::vector<keys_e> &events, float elapsedTime)
{
    float frameRate = 0.1;

    for (auto it = events.begin(); it != events.end(); it++) {
        if (*it == ARROW_DOWN)
            _key = *it;
        else if (*it == ARROW_UP)
            _key = *it;
        else if (*it == ARROW_LEFT)
            _key = *it;
        else if (*it == ARROW_RIGHT)
            _key = *it;
    }
    while (_timer >= frameRate) {
        move();
        refreshBoard();
        _timer -= frameRate;
    }
    if (_timer < frameRate)
        _timer += elapsedTime;
}

bool arcade::game::Pacman::checkBody()
{
    return false;
}

void arcade::game::Pacman::refreshBoard()
{
    initBoard();
    for (auto &cell : _board) {
        if (_pacman.position == cell.position)
            cell = _pacman;
    }
    checkBody();
}

void arcade::game::Pacman::reset()
{
    std::vector<cell_t> newBoard(BOARD_SIZE * BOARD_SIZE);

    _score = 0;
    _board = newBoard;
    initBoard();
}

// GETTERS

const std::vector<arcade::cell_t> &arcade::game::Pacman::getBoard() const
{
    return _board;
}

int arcade::game::Pacman::getScore() const
{
    return _score;
}

// SETTERS

bool arcade::game::Pacman::setBoard(const std::pair<int, int> &pos, const cell_t &cell)
{
    for (auto it = _board.begin(); it != _board.end(); it++)
        if (pos == it->position) {
            *it = cell;
            return true;
        }
    return false;
}

bool arcade::game::Pacman::setScore(const int &score)
{
    if (_score + score < 0) {
        _score = 0;
        return false;
    }
    _score += score;
    return true;
}

// GAMEPLAY

void arcade::game::Pacman::moveHorizontally(int dir)
{
    if (_pacman.position.first + dir < 0 ||
        _pacman.position.second < 0 ||
        _pacman.position.first + dir >= BOARD_SIZE ||
        _pacman.position.second >= BOARD_SIZE)
        return;
    _pacman.position.first += dir;
}

void arcade::game::Pacman::moveVertically(int dir)
{
    if (_pacman.position.first < 0 ||
        _pacman.position.second + dir < 0 ||
        _pacman.position.first >= BOARD_SIZE ||
        _pacman.position.second + dir >= BOARD_SIZE)
        return;
    _pacman.position.second += dir;
}

bool arcade::game::Pacman::move()
{
    if (_key == ARROW_DOWN)
        moveVertically(1);
    else if (_key == ARROW_UP)
        moveVertically(-1);
    else if (_key == ARROW_LEFT)
        moveHorizontally(-1);
    else if (_key == ARROW_RIGHT)
        moveHorizontally(1);
    if (_pacman.position.first < 0 ||
        _pacman.position.second < 0 ||
        _pacman.position.first >= BOARD_SIZE ||
        _pacman.position.second >= BOARD_SIZE)
        return (fprintf(stderr, "Game over\n") && 0);
    return true;
}

void arcade::game::Pacman::eat()
{
}

void arcade::game::Pacman::setTextOnBoard(std::pair<int, int> pos, std::string str)
{
    for (std::size_t i = 0; i < str.length(); i++) {
        for (auto &cell : _board) {
            if (cell.position.first == (pos.first + (int)i) &&
                cell.position.second == pos.second) {
                cell.c = str[i];
                cell.charColor = 0xFFFFFFFF;
                cell.plainChar = true;
            }
        }
    }
}

extern "C" {
	std::unique_ptr<arcade::game::IGameModule> entry_point()
	{
	    return std::make_unique<arcade::game::Pacman>();
	}
}
