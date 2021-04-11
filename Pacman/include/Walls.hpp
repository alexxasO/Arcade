/*
** EPITECH PROJECT, 2021
** Walls.cpp
** File description:
** Walls
*/

#ifndef WALLS_H_
#define WALLS_H_

#define BOARD_SIZE 40

#include <vector>
#include "keys.hpp"
#include "Cell.hpp"


namespace arcade::game
{
    class Walls {
        public:
            Walls()
            {
                std::string map[] = {
                    "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr",
                    "r                                      r",
                    "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr",
                    "r                                      r",
                    "r rrr rrrr rrrr rrr rrr  rrrr rrrrrrrr r",
                    "r r r r  r r    r r r rr r    r      r r",
                    "r r r r  r r    r r r  r r    r      r r",
                    "r r r r  r r    r r r  r r    r      r r",
                    "r r r rrrr r    r r r  r r    r      r r",
                    "r r r rrr  r    r r r  r r    r      r r",
                    "r rrr rrrr r    rrr r  r rrr  r      r r",
                    "r r r r  r r    r r r  r r    r      r r",
                    "r r r r  r r    r r r  r r    r      r r",
                    "r r r r  r r    r r r  r r    r      r r",
                    "r r r r  r r    r r r rr r    r      r r",
                    "r r r r  r rrrr r r rrr  rrrr rrrrrrrr r",
                    "r                                      r",
                    "rrrrrrr rrrrrrr rrr rrr rrrrrrrr rrrrrrr",
                    "                r     r                 ",
                    "rrrrrrrrrrrrrrr r     r rrrrrrrrrrrrrrrr",
                    "rrrrrrrrrrrrrrr r     r rrrrrrrrrrrrrrrr",
                    "                r     r                 ",
                    "rrrrrrr rrrrrrr rrrrrrr rrrrrrrr rrrrrrr",
                    "r                                      r",
                    "r rrrrrrrrrrrrr rrrrrrr rrrrrrrrrrrrrr r",
                    "r r           r r     r r            r r",
                    "r r rrrrrrrrr r r rrr r r rrrrrrrrrr r r",
                    "r r r       r   r rrr r   r        r r r",
                    "r r r rrrrr rrrrr rrr rrrrr rrrrrr r r r",
                    "r r r             rrr              r r r",
                    "r r rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr r r",
                    "r r                                  r r",
                    "r rrrrrrrrrrrrrrrrr rrrrrrrrrrrrrrrrrr r",
                    "r                                      r",
                    "r rr rrrrrr rrrrrrrrrrrrrr rrrrrrrr rr r",
                    "r rr rrrrrr rrrrrrrrrrrrrr rrrrrrrr rr r",
                    "r rr        rrr         rr          rr r",
                    "r rrrrrrrrrrrrr rrrrrrr rrrrrrrrrrrrrr r",
                    "r               rrrrrrr                r",
                    "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr"
                };
                std::size_t move(0);

                for (std::size_t i = 0; i != BOARD_SIZE; i++) {
                    for (std::size_t j = 0; j != BOARD_SIZE; j++) {
                        _walls[move].position = {i, j};
                        _walls[move].c = map[i][j];
                        if (map[i][j] == 'r')
                            _walls[move].charColor = 0x0000FFFF;
                        else
                            _walls[move].charColor = 0x000000FF;
                        move++;
                    }
                }
            };
            ~Walls() {};

            std::vector<cell_t> _walls;
        protected:
        private:
    };
}

#endif /* !WALLS_H_ */
