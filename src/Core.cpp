/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Core
*/

#include "Core.hpp"
#include <iostream>
#include <filesystem>
#include <algorithm>
namespace fs = std::filesystem;

Core::Core(int ac, char *av[])
: _graph_idx(0), _game_idx(0)
{
    _graph_libs_dict = {
        "./lib/arcade_ndk++.so",
        "./lib/arcade_aalib.so",
        "./lib/arcade_libcaca.so",
        "./lib/arcade_allegro5.so",
        "./lib/arcade_xlib.so",
        "./lib/arcade_gtk+.so",
        "./lib/arcade_sfml.so" "arcade_irrlicht.so",
        "./lib/arcade_opengl.so",
        "./lib/arcade_vulkan.so",
        "./lib/arcade_qt5.so"
    };
    _game_libs_dict = {
        "arcade_nibbler.so",
        "arcade_pacman.so",
        "arcade_qix.so",
        "arcade_centipede.so",
        "arcade_solarfox.so"
    };

    for (const auto & entry : fs::directory_iterator("./lib")) {
        if (std::find(_graph_libs_dict.begin(), _graph_libs_dict.end(), entry.path()) != _graph_libs_dict.end()) {
            _graph_libs.push_back(entry.path());
        }
        if (std::find(_game_libs_dict.begin(), _game_libs_dict.end(), entry.path()) != _game_libs_dict.end()) {
            _game_libs.push_back(entry.path());
        }
    }
}

Core::~Core()
{
    dlclose(_graph_lib);
    dlclose(_game_lib);
}

std::string Core::get_next_lib(const bool isGraph)
{
    if (isGraph) {
        if (++_graph_idx >= _graph_libs.size())
            _graph_idx = 0;
        return _graph_libs[_graph_idx];
    } else {
        if (++_game_idx >= _game_libs.size())
            _game_idx = 0;
        return _game_libs[_game_idx];
    }
}

IDisplayModule *Core::load_graph_lib(const char *path)
{
    dlclose(_graph_lib);
    _graph_lib = dlopen(path, RTLD_LAZY);
    if (!_graph_lib)
        return nullptr;
    if ((_graph = (IDisplayModule *)dlsym(_graph_lib, "IDisplayModule")) == NULL)
        return nullptr;
    return _graph;
}

IGameModule *Core::load_game_lib(const char *path)
{
    dlclose(_game_lib);
    _game_lib = dlopen(path, RTLD_LAZY);
    if (!_game_lib)
        return nullptr;
    if ((_game = (IGameModule *)dlsym(_game_lib, "IGameModule")) == NULL)
        return nullptr;
    return _game;
}

bool Core::do_a_frame()
{
    std::vector<keys_e> events = _graph->pollEvent();

    _game->update(events);
    _game->refreshBoard();
    _board = _game->getBoard();
    _score = _game->getScore();
    _graph->interpretCells(_board);
    _graph->refreshScreen();
    usleep(16);
}