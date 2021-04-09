/*
** EPITECH PROJECT, 2021
** Menu.cpp
** File description:
** Menu
*/

#ifndef MENU_H_
#define MENU_H_

#define BOARD_SIZE 40

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <filesystem>
#include <dlfcn.h>
#include <algorithm>
#include <deque>
#include <unistd.h>
#include "Cell.hpp"
#include "keys.hpp"
#include "IGameModule.hpp"

namespace arcade
{
    class Menu {
        public:
            Menu();
            ~Menu();

            /* Member functions */
    		void update(const std::vector<keys_e> &events, float elapsedTime);
            void refreshBoard();
            void reset();

            /* Getters */
            const std::vector<cell_t> &getBoard();
    		int getScore();

            /* Setters */
            bool setBoard(const std::pair<int, int> &, const cell_t &);
    		bool setScore(const int &);
            bool setGameList(std::deque<std::string>);
            void setTextOnBoard(std::pair<int, int>, std::string);

        protected:
        private:
            std::vector<cell_t> _board;
            int _score;
            std::map<std::size_t, std::string> _gameList;
    };
}

#endif /* !Menu_H_ */
