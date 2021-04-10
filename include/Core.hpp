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
#include <memory>
#include <iostream>
#include <chrono>
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "Menu.hpp"

namespace arcade {
class Core {
    public:
        Core(int ac, char *av[]);
        ~Core();

        std::string get_next_lib(const bool isGraph);
        void load_graph_lib(const char *path);
        void load_game_lib(const char *path);
        bool do_a_frame();

    protected:
        std::deque<std::string> _graph_libs_dict;
        std::deque<std::string> _graph_libs;
        int _graph_idx{0};

        std::deque<std::string> _game_libs_dict;
        std::deque<std::string> _game_libs;
        int _game_idx;

        std::unique_ptr<arcade::display::IDisplayModule> (*_graph)(){nullptr};
        std::unique_ptr<arcade::display::IDisplayModule> _libgr{nullptr};
        void *_graph_lib;
        std::unique_ptr<arcade::game::IGameModule> (*_game)(){nullptr};
        std::unique_ptr<arcade::game::IGameModule> _libgm{nullptr};
        void *_game_lib;

        std::chrono::time_point<std::chrono::system_clock> _now;
        std::chrono::duration<float> _elapsed_time;

    private:
        arcade::Menu _menu;
        std::size_t _score;
};
}

#endif /* !CORE_HPP_ */
