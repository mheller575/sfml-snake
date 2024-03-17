/*
*	Copyright (C) 2016 Sidhin S Thomas
*
*	This file is part of sfml-snake.
*
*    sfml-snake is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   sfml-snake is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with sfml-snake.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cstdint>
#include <random>

#include "RandomNumberGenerator.h"

namespace Snake
{
	int GetRandomNumber(const std::int32_t& min, const std::int32_t& max)
	{
		// TODO: Maybe this should be stack allocated? Have a static bool track if we were seeded already? Optional?
		static std::shared_ptr<std::mt19937> generator;

		if (generator == nullptr)
		{
			generator = std::make_shared<std::mt19937>();
			std::random_device rd;
			generator->seed(rd());
		}

		std::uniform_int_distribution<int> dist(min, max);
		return dist(*generator);
	}
}
