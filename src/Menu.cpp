/*
** EPITECH PROJECT, 2021
** Menu.cpp
** File description:
** Menu
*/

#include "Menu.hpp"

arcade::Menu::Menu()
    : _typing(false), _board(BOARD_SIZE * BOARD_SIZE), _score(0), _timer(0), _game("menu")
{
    initBoard();
}

arcade::Menu::~Menu()
{
}

// MEMBER FUNCTIONS

void arcade::Menu::initBoard()
{
    std::size_t move = 0;
    arcade::cell_t newCell;

    for (std::size_t i = 0; i != BOARD_SIZE; i++) {
        for (std::size_t j = 0; j != BOARD_SIZE; j++) {
            _board[move] = newCell;
            _board[move].position = {i, j};
            _board[move].c = ' ';
            _board[move].charColor = 0x000000FF;
            _board[move].bgColor = 0x000000FF;
            if (!i || i == BOARD_SIZE - 1) {
                _board[move].c = 'r';
                _board[move].charColor = 0xFF0000FF;
            }
            if (!j || j == BOARD_SIZE - 1 || j == 6 || j == 12 || j == 26) {
                _board[move].c = 'r';
                _board[move].charColor = 0xFF0000FF;
            }
            move++;
        }
    }
}

std::string arcade::Menu::update(const std::vector<arcade::keys_e> &events, float elapsedTime, const std::size_t &score)
{
    float frameRate = 0.1;

    for (auto it = events.begin(); it != events.end(); it++) {
        if (_typing) {
            if (*it == ESC || *it == DEL) {
                _name = "";
                _typing = false;
            }
            if (*it >= 45 && *it <= 70)
                _name += (*it + '4');
            if (*it == RETURN)
                _typing = false;
        } else {
            if (*it == NUM_1 || *it == NUM_2 || *it == NUM_3 ||
                *it == NUM_4 || *it == NUM_5 || *it == NUM_6 ||
                *it == NUM_7 || *it == NUM_8 || *it == NUM_9) {
                for (auto lst : _gameList) {
                    if ((std::size_t)(*it - 23) == lst.first) {
                        _game = "./lib/arcade_" + lst.second + ".so";
                    }
                }
            }
            if (*it == T) {
                _name = " ";
                _typing = true;
            }
        }
    }
    while (_timer >= frameRate) {
        refreshBoard(score);
        _timer -= frameRate;
    }
    if (_timer < frameRate)
        _timer += elapsedTime;
    return _game;
}

void arcade::Menu::refreshBoard(const std::size_t &score)
{
    std::pair<int, int> pos(5, 16);
    std::pair<int, int> pos2(5, 30);

    initBoard();
    setTextOnBoard({17, 2}, "ARCADE");
    setTextOnBoard({15, 4}, "score = " + std::to_string(score));
    // setTextOnBoard({1, 6}, "--------------------------------------");
    setTextOnBoard({2, 8}, "Enter your name: press <T>");
    setTextOnBoard({5, 10}, ((_name != "") ? _name : "_______________"));
    // setTextOnBoard({1, 12}, "--------------------------------------");
    setTextOnBoard({12, 14}, "Select a game");
    for (auto lst : _gameList) {
        setTextOnBoard({pos.first, pos.second++},
                        lst.second + ": press <" + std::to_string(lst.first) + ">");
    }
    // setTextOnBoard({1, 26}, "--------------------------------------");
    setTextOnBoard({8, 28}, "List of graphic libraries:");
    for (auto lst : _graphList) {
        setTextOnBoard({pos2.first, pos2.second++}, "- " + lst);
    }
}

void arcade::Menu::reset()
{
    std::vector<cell_t> newBoard(BOARD_SIZE * BOARD_SIZE);

    _score = 0;
    _board = newBoard;
}

// GETTERS

const std::vector<arcade::cell_t> &arcade::Menu::getBoard() const
{
    return _board;
}

int arcade::Menu::getScore() const
{
    return _score;
}

std::string arcade::Menu::getGame() const
{
    return _game;
}

// SETTERS

bool arcade::Menu::setBoard(const std::pair<int, int> &pos, const cell_t &cell)
{
    for (auto it = _board.begin(); it != _board.end(); it++)
        if (pos == it->position) {
            *it = cell;
            return true;
        }
    return false;
}

bool arcade::Menu::setScore(const int &score)
{
    if (_score - score < 0) {
        _score = 0;
        return false;
    }
    _score += score;
    return true;
}

bool arcade::Menu::setGameList(const std::deque<std::string> &gameList,
                               const std::deque<std::string> &graphList)
{
    bool flag = false;
    std::string path("./lib");
    std::string temp;
    std::pair<int, int> idx(0, 1);
    std::vector<std::string> strings;

    for (auto lst : gameList) {
        temp = (lst.c_str() + 13);
        if ((idx.first = temp.find(".so"))) {
            _gameList[idx.second] = temp.erase(idx.first, 3);
            idx.second++;
        }
    }
    idx = {0, 1};
    for (auto lst : graphList) {
        temp = (lst.c_str() + 13);
        if ((idx.first = temp.find(".so"))) {
            _graphList.push_back(temp.erase(idx.first, 3));
        }
    }

    return flag;
}

void arcade::Menu::setTextOnBoard(std::pair<int, int> pos, std::string str)
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

void arcade::Menu::setGame(const std::string &game)
{
    _game = game;
}
