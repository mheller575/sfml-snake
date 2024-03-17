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

#pragma once

#include <cstdint>
#include <list>
#include <optional>

#include <SFML/Graphics.hpp>

#include "IComponent.h"

namespace Snake
{
	enum class Direction
	{
		Up,
		Right,
		Down,
		Left,
	};

	class SnakeComponent : public IComponent
	{
	public:
		SnakeComponent(const std::int32_t& startingX, const std::int32_t& startingY, const Direction& startingDirection, const sf::Color& headColor, const sf::Color& bodyColor);

		void Draw(sf::RenderWindow& window) const override;

		void NextDirection(const Direction& nextDirection);

		void DecreaseLength();

		bool OverlapsRectangle(const sf::RectangleShape& rectangle) const;

		bool DoesSnakeCrossItself() const;

		bool DoesSnakeLeaveWindow(const std::int32_t& x, const std::int32_t& y);

	private:
		const sf::Color _headColor;
		const sf::Color _bodyColor;

		Direction _lastDirection;
		std::list<sf::RectangleShape> _snake;
	};
}
