/*
** EPITECH PROJECT, 2021
** arcade-B-400
** File description:
** main
*/

#include "Core.hpp"

static void print_usage(char *name)
{
    fprintf(stderr, "Usage: ./%s path\n    path :\n    \
        path to the lib to load at the start of the program\n", name);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Error: Invalid arguments" << std::endl;
        print_usage(av[0]);
        return 84;
    }
    arcade::Core c(ac, av);

    while (1) {
        try {
            if (!c.do_a_frame())
                break;
        } catch(const std::exception& e) {
            std::cerr << e.what() << std::endl;
            print_usage(av[0]);
            return 84;
        }
    }
    return 0;
}
