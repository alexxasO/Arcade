/*
** EPITECH PROJECT, 2021
** Nibbler_game_module.cpp
** File description:
** Nibbler_game_module
*/

#include "Nibbler_game_module.hpp"

arcade::game::Nibbler_game_module::Nibbler_game_module()
    : _board(BOARD_SIZE * BOARD_SIZE), _score(0), _snake(4), _fruits(1), _timer(0)
{
    initBoard();
}

arcade::game::Nibbler_game_module::~Nibbler_game_module()
{
}

// MEMBER FUNCTIONS

void arcade::game::Nibbler_game_module::initBoard()
{
    std::size_t move = 0;
    arcade::cell_t newCell;

    for (std::size_t i = 0; i != BOARD_SIZE; i++) {
        for (std::size_t j = 0; j != BOARD_SIZE; j++) {
            _board[move] = newCell;
            _board[move].position = {i, j};
            _board[move].c = ' ';
            _board[move].charColor = 0x000000FF;
            if (!i || i == BOARD_SIZE - 1) {
                _board[move].c = 'r';
                _board[move].charColor = 0xFF0000FF;
            }
            if (!j || j == BOARD_SIZE - 1 || j == 2) {
                _board[move].c = 'r';
                _board[move].charColor = 0xFF0000FF;
            }
            move++;
        }
    }
    setTextOnBoard({1, 1}, "NIBBLER");
    setTextOnBoard({12, 1}, "Score : " + std::to_string(_score));
}

void arcade::game::Nibbler_game_module::update(const std::vector<keys_e> &events, float elapsedTime)
{
    float frameRate = 0.1;

    for (auto it = events.begin(); it != events.end(); it++) {
        if (*it == ARROW_DOWN && _snake._key != ARROW_UP)
            _snake._key = *it;
        else if (*it == ARROW_UP && _snake._key != ARROW_DOWN)
            _snake._key = *it;
        else if (*it == ARROW_LEFT && _snake._key != ARROW_RIGHT)
            _snake._key = *it;
        else if (*it == ARROW_RIGHT && _snake._key != ARROW_LEFT)
            _snake._key = *it;
    }
    while (_timer >= frameRate) {
        if (!move())
            return;
        refreshBoard();
        _timer -= frameRate;
    }
    if (_timer < frameRate)
        _timer += elapsedTime;
}

bool arcade::game::Nibbler_game_module::checkBody()
{
    for (auto it = _snake._Snake.begin(); it != _snake._Snake.end(); it++) {
        for (auto jt = _snake._Snake.begin(); jt != _snake._Snake.end(); jt++) {
            if (it != jt && it->position == jt->position) {
                reset();
                return true;
            }
        }
    }
    return false;
}

void arcade::game::Nibbler_game_module::refreshBoard()
{
    initBoard();
    for (auto &cell : _board) {
        for (auto &food : _fruits._apple) {
            if (food.position.first == cell.position.first &&
                food.position.second == cell.position.second) {
                cell = food;
            }
        }
        if (_snake._Snake.begin()->position == cell.position) {
            if (cell.c == 'o') {
                eat();
            }
            if (cell.c == 'r') {
                reset();
                return;
            }
        }
        for (auto &snake : _snake._Snake) {
            if (snake.position.first == cell.position.first &&
                snake.position.second == cell.position.second) {
                cell = snake;
            }
        }
    }
    checkBody();
}

void arcade::game::Nibbler_game_module::reset()
{
    std::vector<cell_t> newBoard(BOARD_SIZE * BOARD_SIZE);
    Snake newSnake(4);
    Fruit newFruits(1);
    std::size_t move = 0;

    _score = 0;
    _board = newBoard;
    _snake = newSnake;
    _fruits = newFruits;
    initBoard();
}

// GETTERS

const std::vector<arcade::cell_t> &arcade::game::Nibbler_game_module::getBoard() const
{
    return _board;
}

int arcade::game::Nibbler_game_module::getScore() const
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
    if (_score + score < 0) {
        _score = 0;
        return false;
    }
    _score += score;
    return true;
}

// GAMEPLAY

void arcade::game::Nibbler_game_module::moveHorizontally(int dir)
{
    std::pair<int, int> first = _snake._Snake.begin()->position;
    std::pair<int, int> posTemp1 = _snake._Snake.begin()->position;
    std::pair<int, int> posTemp2 = _snake._Snake.begin()->position;

    _lastPos = _snake._Snake.at(_snake._size - 1);
    for (auto it = _snake._Snake.begin() + 1; it != _snake._Snake.end(); it++) {
        posTemp2 = it->position;
        it->position = {posTemp1.first, posTemp1.second};
        posTemp1 = posTemp2;
    }
    _snake._Snake.begin()->position = {first.first + dir, first.second};
}

void arcade::game::Nibbler_game_module::moveVertically(int dir)
{
    std::pair<int, int> first = _snake._Snake.begin()->position;
    std::pair<int, int> posTemp1 = _snake._Snake.begin()->position;
    std::pair<int, int> posTemp2 = _snake._Snake.begin()->position;

    _lastPos = _snake._Snake.at(_snake._size - 1);
    for (auto it = _snake._Snake.begin() + 1; it != _snake._Snake.end(); it++) {
        posTemp2 = it->position;
        it->position = {posTemp1.first, posTemp1.second};
        posTemp1 = posTemp2;
    }
    _snake._Snake.begin()->position = {first.first, first.second + dir};
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
        _snake._Snake.begin()->position.second >= BOARD_SIZE)
        return false;
    return true;
}

void arcade::game::Nibbler_game_module::eat()
{
    std::pair<int, int> pos;
    bool found = false;

    _snake._size++;
    setScore(20);
    _snake._Snake.push_back(_lastPos);
    while (!found) {
        pos = {BLIMX, BLIMY};
        for (auto cell : _board) {
            if (cell.position == pos && cell.c == ' ')
                found = true;
        }
    }
    _fruits._apple.begin()->position = pos;
}

void arcade::game::Nibbler_game_module::setTextOnBoard(std::pair<int, int> pos, std::string str)
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
	    return std::make_unique<arcade::game::Nibbler_game_module>();
	}
}
