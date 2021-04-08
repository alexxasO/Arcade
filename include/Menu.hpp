/*
** EPITECH PROJECT, 2021
** Menu.cpp
** File description:
** Menu
*/

#ifndef Menu_h
#define Menu_h

#define BOARD_SIZE 40

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <filesystem>
#include <dlfcn.h>
#include <algorithm>
#include "Cell.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"
#include "IGameModule.hpp"

class Menu : public game::IGameModule {
    public:
        Menu();
        ~Menu();

        /* Member functions */
		void update(std::vector<keys_e> &events);
        void refreshBoard();
        void reset();

        /* Getters */
        const std::vector<cell_t> &getBoard();
		int getScore();

        /* Setters */
        bool setBoard(const std::pair<int, int> &, const cell_t &);
		bool setScore(const int &);
        bool setGameList();
        void setTextOnBoard(std::pair<int, int>, std::string);

    protected:
    private:
        std::vector<cell_t> _board;
        int _score;
        std::map<std::size_t, std::string> _gameList;
};

#endif /* !Menu_h */
