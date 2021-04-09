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
#include <unistd.h>
namespace fs = std::filesystem;

arcade::Core::Core(int ac, char *av[])
: _graph_idx(0), _game_idx(0), _graph_lib(nullptr), _game_lib(nullptr)
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

    if (ac == 2) {
        load_graph_lib(av[1]);
        load_game_lib("./lib/arcade_nibbler.so");
    }
}

arcade::Core::~Core()
{
    if (_graph_lib)
        dlclose(_graph_lib);
    if (_game_lib)
        dlclose(_game_lib);
}

std::string arcade::Core::get_next_lib(const bool isGraph)
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

void arcade::Core::load_graph_lib(const char *path)
{
    if (_graph_lib) {
        dlclose(_graph_lib);
        _graph_lib = nullptr;
    }
    _graph_lib = dlopen(path, RTLD_NOW);
    if (!_graph_lib)
        exit(84);
    if ((_graph = (std::unique_ptr<arcade::display::IDisplayModule> (*)())dlsym(_graph_lib, "entry_point")) == NULL)
        exit(84);
    _libgr = _graph();
}

void arcade::Core::load_game_lib(const char *path)
{
    if (_game_lib) {
        dlclose(_game_lib);
        _game_lib = nullptr;
    }
    _game_lib = dlopen(path, RTLD_LAZY);
    if (!_game_lib)
        exit(84);
    if ((_game = (std::unique_ptr<arcade::game::IGameModule> (*)())dlsym(_game_lib, "entry_point")) == NULL)
        exit(84);
    _libgm = _game();
}

bool arcade::Core::do_a_frame()
{
    std::vector<keys_e> events = _libgr->pollEvent();
    // std::vector<keys_e> events = {ADD};

    std::cerr << _libgm->getScore() << std::endl;
    _libgm->update(events, 0);
    _libgr->interpretCells(_libgm->getBoard());
    _libgr->refreshScreen();
    usleep(10000000);
    return true;
}
