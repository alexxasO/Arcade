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
        "./lib/arcade_sfml.so",
        "./lib/arcade_sdl2.so",
        "./lib/arcade_irrlicht.so",
        "./lib/arcade_opengl.so",
        "./lib/arcade_vulkan.so",
        "./lib/arcade_qt5.so"
    };
    _game_libs_dict = {
        "./lib/arcade_nibbler.so",
        "./lib/arcade_pacman.so",
        "./lib/arcade_qix.so",
        "./lib/arcade_centipede.so",
        "./lib/arcade_solarfox.so"
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
        try {
            load_graph_lib(av[1]);
            load_game_lib(_game_libs[0].c_str());
            _now = std::chrono::system_clock::now();
        } catch(const std::exception& e) {
            fprintf(stderr, "%s", e.what());
            exit(84);
        }
    }
}

arcade::Core::~Core()
{
    _libgr.reset();
    _libgm.reset();
    if (_graph_lib)
        dlclose(_graph_lib);
    if (_game_lib)
        dlclose(_game_lib);
}

std::string arcade::Core::get_prev_lib(const bool isGraph)
{
    if (isGraph) {
        if (_graph_idx-- <= 0)
            _graph_idx = _graph_libs.size() - 1;
        return _graph_libs[_graph_idx];
    } else {
        if (_game_idx-- <= 0)
            _game_idx = _game_libs.size() - 1;
        return _game_libs[_game_idx];
    }
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
    if (path)
        _last_path_graph = path;
    if (_graph_lib) {
        _libgr.reset();
        dlclose(_graph_lib);
        _graph_lib = nullptr;
    }
    _graph_lib = dlopen(path, RTLD_LAZY);
    if (!_graph_lib)
        throw std::runtime_error("Display Module : failed to load lib");
    if ((_graph = (std::unique_ptr<arcade::display::IDisplayModule> (*)())dlsym(_graph_lib, "entry_point")) == NULL)
        throw std::runtime_error("Display Module : failed to load symbol");
    _libgr = _graph();
}

void arcade::Core::load_game_lib(const char *path)
{
    if (path)
        _last_path_game = path;
    if (_game_lib) {
        _libgm.reset();
        dlclose(_game_lib);
        _game_lib = nullptr;
    }
    _game_lib = dlopen(path, RTLD_LAZY);
    if (!_game_lib)
        throw std::runtime_error("Game Module : failed to load lib");
    if ((_game = (std::unique_ptr<arcade::game::IGameModule> (*)())dlsym(_game_lib, "entry_point")) == NULL)
        throw std::runtime_error("Game Module : failed to load symbol");
    _libgm = _game();
}

bool arcade::Core::interpret_events(std::vector<keys_e> &events) {
    for (const auto & key : events) {
        if (key == ESC) {
            remove(events.begin(), events.end(), key);
            return false;
        } else if (key == F1) {
            remove(events.begin(), events.end(), key);
            load_graph_lib(get_prev_lib(true).c_str());
        } else if (key == F2) {
            remove(events.begin(), events.end(), key);
            load_graph_lib(get_next_lib(true).c_str());
        } else if (key == F3) {
            remove(events.begin(), events.end(), key);
            load_game_lib(get_prev_lib(false).c_str());
        } else if (key == F4) {
            remove(events.begin(), events.end(), key);
            load_game_lib(get_next_lib(false).c_str());
        } else if (key == R) { // FIXME: segV
            remove(events.begin(), events.end(), key);
            load_game_lib(_last_path_game.c_str());
        }
    }
    return true;
}

bool arcade::Core::do_a_frame()
{
    std::vector<keys_e> events = _libgr->pollEvent();

    if (!interpret_events(events)) {
        return false;
    }
    _elapsed_time = std::chrono::system_clock::now() - _now;
    _now = std::chrono::system_clock::now();
    _libgm->update(events, _elapsed_time.count());
    _libgr->interpretCells(_libgm->getBoard());
    _libgr->refreshScreen();
    return true;
}