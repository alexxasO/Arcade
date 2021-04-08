/*
** EPITECH PROJECT, 2021
** Fruit.cpp
** File description:
** Fruit
*/

#ifndef FRUIT_H_
#define FRUIT_H_

#define BOARD_SIZE 40
#define RD(x)   (rand() % x)
#define RDCOLOR ((((((0xFF << 8) + RD(0x88)) << 8) + RD(0x88)) << 8) + 0xFF)

class Fruit {
    public:
        Fruit(const size_t &nb)
            : _id(0), _apple(nb), _score(20)
        {
            for (std::size_t i = 0; i != nb; i++) {
                srand(time(NULL));
                _apple[i].position = {rand() % BOARD_SIZE, rand() % BOARD_SIZE};
                _apple[i].c = 'o';
                _apple[i].charColor = RDCOLOR;
            }
        };
        ~Fruit();

        std::size_t _id;
        std::vector<cell_t> _apple;
        std::size_t _score;
    protected:
    private:
};

#endif /* !FRUIT_H_ */
