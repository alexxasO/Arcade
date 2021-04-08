/*
** EPITECH PROJECT, 2021
** Snake.cpp
** File description:
** Snake
*/

#ifndef Snake_h
#define Snake_h

#define BOARD_SIZE 40

class Snake {
    public:
        Snake(const size_t &nb)
            : _size(0), _Snake(nb)
        {
            std::pair<int, int> center(BOARD_SIZE / 2, BOARD_SIZE / 2);

            for (std::size_t i = 0; i != nb; i++) {
                srand(time(NULL));
                _Snake[i].position = {center.first - i, center.second};
                _Snake[i].c = '0';
                _Snake[i].charColor = (!i ? 0xBE8AB088 : 0xBE8AB0FF);
                _Snake[i].bgColor = (!i ? 0x000000FF : 0xBE8AB0FF);
            }
        };
        ~Snake();

        std::size_t _size;
        std::vector<cell_t> _Snake;
    protected:
    private:
};

#endif /* !Snake_h */
