/*
** EPITECH PROJECT, 2021
** Menu.cpp
** File description:
** Menu
*/

#include "Menu.hpp"

arcade::Menu::Menu()
    : _board(BOARD_SIZE * BOARD_SIZE), _score(0), _timer(0)
{
    std::size_t move = 0;

    for (std::size_t i = 0; i != BOARD_SIZE; i++) {
        for (std::size_t j = 0; j != BOARD_SIZE; j++) {
            _board[move].position = {i, j};
            if (!i || i == BOARD_SIZE - 1) {
                _board[move].c = '|';
                _board[move].charColor = 0xFFFF88FF;
            }
            if (!j || j == BOARD_SIZE - 1) {
                _board[move].c = '-';
                _board[move].charColor = 0xFFFF88FF;
            }
            move++;
        }
    }
}

arcade::Menu::~Menu()
{
}

// MEMBER FUNCTIONS

std::string arcade::Menu::update(const std::vector<arcade::keys_e> &events, float elapsedTime, const std::size_t &score)
{
    float frameRate = 0.1;

    fprintf(stderr, "(timer = %f, elapse = %f)\n", _timer, elapsedTime);
    for (auto it = events.begin(); it != events.end(); it++) {
        if (*it == NUM_1 || *it == NUM_2 || *it == NUM_3 ||
            *it == NUM_4 || *it == NUM_5 || *it == NUM_6 ||
            *it == NUM_7 || *it == NUM_8 || *it == NUM_9) {
            fprintf(stderr, "game %s has been launched\n", _gameList[*it].c_str());
            return _gameList[*it].c_str();
        }
    }
    while (_timer >= frameRate) {
        refreshBoard(score);
        _timer -= frameRate;
    }
    if (_timer < frameRate)
        _timer += elapsedTime;
    return "menu";
}

void arcade::Menu::refreshBoard(const std::size_t &score)
{
    std::pair<int, int> pos(2, BOARD_SIZE / 2);

    setTextOnBoard({2, 2}, "ARCADE");
    setTextOnBoard({2, 5}, "score = " + std::to_string(score));
    setTextOnBoard({2, 15}, "Select a game");
    for (auto lst : _gameList) {
        setTextOnBoard({pos.first, pos.second += 2},
                        lst.second + " " + std::to_string(lst.first));
    }
}

void arcade::Menu::reset()
{
    std::vector<cell_t> newBoard(BOARD_SIZE * BOARD_SIZE);

    _score = 0;
    _board = newBoard;
}

// GETTERS

const std::vector<arcade::cell_t> &arcade::Menu::getBoard()
{
    return _board;
}

int arcade::Menu::getScore()
{
    return _score;
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

bool arcade::Menu::setGameList(const std::deque<std::string> &gameList)
{
    bool flag = false;
    std::string path("./lib");
    std::string temp;
    std::pair<int, int> idx(0, 1);
    std::vector<std::string> strings;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        temp = (entry.path().c_str() + 6);
        if ((idx.first = temp.find(".so"))) {
            for (auto lst : gameList) {
                if (lst == temp) {
                    _gameList[idx.second] = temp.erase(idx.first, 3);
                    fprintf(stderr, "> str = %s\n", _gameList[idx.second].c_str());
                    idx.second++;
                }
            }
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
                cell.plainChar = true;
            }
        }
    }
}
