/*
** EPITECH PROJECT, 2021
** arcade-B-400
** File description:
** Entry_point
*/

#ifndef ENTRY_POINT_HPP_
#define ENTRY_POINT_HPP_

#include <memory>
#include "IGameModule.hpp"
#include "Nibbler_game_module.hpp"

extern "C" {

	std::unique_ptr<arcade::game::IGameModule> entry_point()
	{
	    return std::make_unique<arcade::game::Nibbler_game_module>();
	}
}

#endif /* !ENTRY_POINT_HPP_ */
