/*
** EPITECH PROJECT, 2021
** arcade-B-400
** File description:
** main
*/

#include "Core.hpp"

int main(int ac, char **av)
{
    arcade::Core c(ac, av);

    while (1) {
        if (!c.do_a_frame())
            break;
    }

    return 0;
}
