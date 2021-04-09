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
    std::size_t move = 0;

    for (std::size_t i = 0; i != BOARD_SIZE; i++) {
        for (std::size_t j = 0; j != BOARD_SIZE; j++) {
            _board[move].position = {i, j};
            move++;
        }
    }
}

arcade::game::Nibbler_game_module::~Nibbler_game_module()
{
}

// MEMBER FUNCTIONS

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
        if (*it == R)
            reset();
    }
    while (_timer >= frameRate) {
        move();
        refreshBoard();
        _timer -= frameRate;
    }
    if (_timer < frameRate)
        _timer += elapsedTime;
}

void arcade::game::Nibbler_game_module::refreshBoard()
{
    arcade::cell_t newCell;

    for (auto &cell : _board) {
        newCell.position = cell.position;
        cell = newCell;
        for (auto &food : _fruits._apple) {
            if (food.position.first == cell.position.first &&
                food.position.second == cell.position.second) {
                cell = food;
            }
        }
        if (_snake._Snake.begin()->position == cell.position) {
            if (cell.c == 'o')
                eat();
            if (cell.c == 'r')
                fprintf(stderr, "Game over\n");
        }
        for (auto &snake : _snake._Snake) {
            if (snake.position.first == cell.position.first &&
                snake.position.second == cell.position.second) {
                cell = snake;
            }
        }
    }
}

void arcade::game::Nibbler_game_module::reset()
{
    std::vector<cell_t> newBoard(BOARD_SIZE * BOARD_SIZE);
    Snake newSnake(4);
    Fruit newFruits(1);
    std::size_t move = 0;

    for (std::size_t i = 0; i != BOARD_SIZE; i++) {
        for (std::size_t j = 0; j != BOARD_SIZE; j++) {
            _board[move].position = {i, j};
            move++;
        }
    }
    _score = 0;
    _board = newBoard;
    _snake = newSnake;
    _fruits = newFruits;
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
    cell_t temp = _snake._Snake.at(0);

    _lastPos = _snake._Snake.at(_snake._size - 1);
    for (auto it = _snake._Snake.begin() + 1; it != _snake._Snake.end(); it++) {
        it->position = {(it - 1)->position.first, (it - 1)->position.second};
    }
    _snake._Snake.begin()->position = {temp.position.first + dir, temp.position.second};
}

void arcade::game::Nibbler_game_module::moveVertically(int dir)
{
    cell_t temp = _snake._Snake.at(0);

    _lastPos = _snake._Snake.at(_snake._size - 1);
    for (auto it = _snake._Snake.begin() + 1; it != _snake._Snake.end(); it++) {
        it->position = {(it - 1)->position.first, (it - 1)->position.second};
    }
    _snake._Snake.begin()->position = {temp.position.first, temp.position.second + dir};
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
        return (fprintf(stderr, "Game over\n") && 0);
    return true;
}

void arcade::game::Nibbler_game_module::eat()
{
    _snake._size++;
    setScore(_fruits._score);
    _snake._Snake.insert(_snake._Snake.end(), _lastPos);
    _fruits._apple.begin()->position = {rand() % BOARD_SIZE, rand() % BOARD_SIZE};
    fprintf(stderr, "Miam\n");
}

extern "C" {
	std::unique_ptr<arcade::game::IGameModule> entry_point()
	{
	    return std::make_unique<arcade::game::Nibbler_game_module>();
	}
}
