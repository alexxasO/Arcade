/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <dlfcn.h>
#include <string>
#include <vector>
#include <deque>
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

const std::string graphic_strings = {};

class Core {
    public:
        Core(int ac, char *av[]);
        ~Core();

        std::string get_next_lib(const bool isGraph);
        IDisplayModule *load_graph_lib(const char *path);
        IGameModule *load_game_lib(const char *path);
        bool do_a_frame();

    protected:
        std::deque<std::string> _graph_libs_dict;
        std::deque<std::string> _graph_libs;
        int _graph_idx;

        std::deque<std::string> _game_libs_dict;
        std::deque<std::string> _game_libs;
        int _game_idx;

        IDisplayModule *_graph;
        void *_graph_lib;
        IGameModule *_game;
        void *_game_lib;

        std::vector<cell_t> _board;
        int _score;

    private:
};

#endif /* !CORE_HPP_ */
