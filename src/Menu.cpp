/*
** EPITECH PROJECT, 2021
** Menu.cpp
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu()
    : _board(BOARD_SIZE * BOARD_SIZE), _score(0)
{
    std::pair<int, int> pos(2, 20);

    setGameList();
    setTextOnBoard({2, 2}, "ARCADE");
    setTextOnBoard({2, 15}, "Select a game");
    for (auto it = _gameList.begin(); it != _gameList.end(); it++) {
        setTextOnBoard({pos.first, pos.second += 2},
                        it->second + " " + std::to_string(it->first));
    }
}

Menu::~Menu()
{
}

// MEMBER FUNCTIONS

void Menu::update(std::vector<keys_e> &events)
{
    for (auto it = events.begin(); it != events.end(); it++) {
        if (*it == NUM_1 || *it == NUM_2 || *it == NUM_3 ||
            *it == NUM_4 || *it == NUM_5 || *it == NUM_6 ||
            *it == NUM_7 || *it == NUM_8 || *it == NUM_9)
            fprintf(stderr, "game %s has been launched\n", _gameList[*it].c_str());
        if (*it == Q)
            fprintf(stderr, "You left the game\n");
    }
}

void Menu::refreshBoard()
{
}

void Menu::reset()
{
    std::vector<cell_t> newBoard(BOARD_SIZE * BOARD_SIZE);

    _score = 0;
    _board = newBoard;
}

// GETTERS

const std::vector<cell_t> &Menu::getBoard()
{
    return _board;
}

int Menu::getScore()
{
    return _score;
}

// SETTERS

bool Menu::setBoard(const std::pair<int, int> &pos, const cell_t &cell)
{
    for (auto it = _board.begin(); it != _board.end(); it++)
        if (pos == it->position) {
            *it = cell;
            return true;
        }
    return false;
}

bool Menu::setScore(const int &score)
{
    if (_score - score < 0) {
        _score = 0;
        return false;
    }
    _score += score;
    return true;
}

bool Menu::setGameList()
{
    void *lib;
    bool flag = false;
    std::string path("./lib");
    std::string temp;
    std::pair<std::size_t, std::size_t> idx;
    std::vector<std::string> strings;
    std::size_t index;

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        temp = (entry.path().c_str() + 6);
        idx.first = temp.find(".so");
        strings[idx.second++] = temp.erase(idx.first, 3);
    }
    for (auto it = strings.begin(); it != strings.end(); it++) {
        path = "./lib/";
        temp = ".so";
        if ((lib = dlopen((path + *it + temp).c_str(), RTLD_LAZY))) {
            if (dlsym(lib, "update")) {
                _gameList[index++] = *it;
                flag = true;
            }
            dlclose(lib);
        }
    }
    return flag;
}

void Menu::setTextOnBoard(std::pair<int, int> pos, std::string str)
{
    for (std::size_t i = 0; i < str.length(); i++) {
        for (auto it = _board.begin(); it != _board.end(); it++) {
            if (it->position.first == (pos.first + (int)i) &&
                it->position.second == pos.second)
                it->c = str[i];
        }
    }
}
