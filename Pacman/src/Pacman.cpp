/*
** EPITECH PROJECT, 2021
** Pacman.cpp
** File description:
** Pacman
*/

#include "Pacman.hpp"

arcade::game::Pacman::Pacman()
    : _board(BOARD_SIZE * BOARD_SIZE), _score(0), _timer(0),
    _key(ARROW_UP), _food(BOARD_SIZE * BOARD_SIZE),
    _smooth(false)
{
    Enemies en1(0);
    Enemies en2(1);
    Enemies en3(2);
    Enemies en4(3);

    _enemies.push_back(en1);
    _enemies.push_back(en2);
    _enemies.push_back(en3);
    _enemies.push_back(en4);
    _pacman = {
        .c = 'o',
        .charColor = 0xFFFF00FF,
        .position = {19, 23}
    };
    initBoard();
}

arcade::game::Pacman::~Pacman()
{
}

// MEMBER FUNCTIONS

void arcade::game::Pacman::initBoard()
{
    _board = _walls._walls;
    for (std::size_t i = 0; i < (BOARD_SIZE * BOARD_SIZE); i++) {
        if (_board[i].c == ' ' && !_food[i]._picked) {
            _board[i].c = _food[i]._food.c;
            _board[i].charColor = _food[i]._food.charColor;
            _board[i].size = _food[i]._food.size;
        } else {
            _food[i]._picked = true;
        }
    }
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
    for (auto &en : _enemies) {
        en.setTimer(elapsedTime);
    }
    while (_timer >= frameRate) {
        for (auto &en : _enemies)
            en.move(_board);
        move();
        refreshBoard();
        _timer -= frameRate;
    }
    if (_timer < frameRate)
        _timer += elapsedTime;
}

bool arcade::game::Pacman::checkBody()
{
    for (auto &food : _food) {
        if (!food._picked)
            return false;
    }
    return true;
}

void arcade::game::Pacman::refreshBoard()
{
    initBoard();
    for (auto &cell : _board) {
        if (_pacman.position == cell.position)
            cell = _pacman;
        for (auto en : _enemies) {
            if (en._enemy.position == cell.position) {
                cell = en._enemy;
            }
        }
    }
    if (checkBody())
        reset();
}

void arcade::game::Pacman::reset()
{
    std::vector<cell_t> newBoard(BOARD_SIZE * BOARD_SIZE);
    Enemies en1(0);
    Enemies en2(1);
    Enemies en3(2);
    Enemies en4(3);
    std::vector<Enemies> enemies;
    std::vector<Food> food(BOARD_SIZE * BOARD_SIZE);

    enemies.push_back(en1);
    enemies.push_back(en2);
    enemies.push_back(en3);
    enemies.push_back(en4);
    _enemies = enemies;
    _pacman = {
        .c = 'o',
        .charColor = 0xFFFF00FF,
        .position = {19, 23}
    };
    _food = food;
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
    std::pair<int, int> newPos = _pacman.position;

    newPos.first += dir;
    for (std::size_t i = 0; i < (BOARD_SIZE * BOARD_SIZE); i++) {
        if (_board[i].position == newPos && _board[i].c == 'r')
            return;
        if (_board[i].position == newPos && _board[i].c == 'o') {
            if (_board[i].size == 1.0) {
                reset();
            } else {
                _score += 10;
                _food[i]._picked = true;
            }
        }
    }
    _pacman.position.first += dir;
    if (_pacman.position.first < 0)
        _pacman.position.first = BOARD_SIZE;
    else if (_pacman.position.first >= BOARD_SIZE)
        _pacman.position.first = (-1);
}

void arcade::game::Pacman::moveVertically(int dir)
{
    std::pair<int, int> newPos = _pacman.position;

    newPos.second += dir;
    for (std::size_t i = 0; i < (BOARD_SIZE * BOARD_SIZE); i++) {
        if (_board[i].position == newPos && _board[i].c == 'r')
            return;
        if (_board[i].position == newPos && _board[i].c == 'o') {
            _score += 10;
            _food[i]._picked = true;
        }
    }
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
