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

#include <list>

#include <SFML/Graphics.hpp>

namespace Snake
{
	enum class Direction
	{
		Up,
		Right,
		Down,
		Left,
	};

	class SnakeComponent
	{
	public:
		SnakeComponent(const int& startingX, const int& startingY, const Direction& startingDirection, const sf::Color& headColor, const sf::Color& bodyColor);

		void Draw(sf::RenderWindow& window) const;

		void NextDirection(const Direction& nextDirection, const bool& increaseLength);

		bool OverlapsRectangle(const sf::RectangleShape& rectangle) const;

		bool DoesSnakeCrossItself() const;

		bool DoesSnakeLeaveWindow(const int& x, const int& y);

	private:
		const sf::Color _headColor;
		const sf::Color _bodyColor;

		std::list<sf::RectangleShape> _snake;
	};
}
