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

#include "SnakeComponent.h"
#include "Utilities.h"

namespace Snake
{
	SnakeComponent::SnakeComponent(const int& startingX, const int& startingY, const Direction& startingDirection, const sf::Color& headColor, const sf::Color& bodyColor)
		: _headColor(headColor)
		, _bodyColor(bodyColor)
	{
		_snake.push_front(BuildRectangleShape(sf::Vector2f(startingX, startingY), headColor));
	}

	void SnakeComponent::Draw(sf::RenderWindow& window) const
	{
		for (auto i = _snake.rbegin(); i != _snake.rend(); ++i)
		{
			window.draw(*i);
		}
	}

	void SnakeComponent::NextDirection(const Direction& nextDirection, const bool& increaseLength)
	{
		int x = _snake.front().getPosition().x;
		int y = _snake.front().getPosition().y;

		switch (nextDirection)
		{
		case Direction::Up:
			y -= BoxSize;
			break;
		case Direction::Right:
			x += BoxSize;
			break;
		case Direction::Down:
			y += BoxSize;
			break;
		case Direction::Left:
			x -= BoxSize;
			break;
		default:
			throw std::exception("Unknown direction provided.");
		}

		_snake.front().setFillColor(_bodyColor);
		_snake.push_front(BuildRectangleShape(sf::Vector2f(x, y), _headColor));

		if (!increaseLength)
		{
			_snake.pop_back();
		}
	}

	bool SnakeComponent::OverlapsRectangle(const sf::RectangleShape& rectangle) const
	{
		return DoRectanglesOverlap(rectangle, _snake.front());
	}

	bool SnakeComponent::DoesSnakeCrossItself() const
	{
		for (auto i = _snake.begin(); i != _snake.end(); ++i)
		{
			if (i != _snake.begin() && DoRectanglesOverlap(_snake.front(), *i))
			{
				return true;
			}
		}

		return false;
	}

	bool SnakeComponent::DoesSnakeLeaveWindow(const int& maxX, const int& maxY)
	{
		int x = _snake.front().getGlobalBounds().left;
		int y = _snake.front().getGlobalBounds().top;
		return (x > maxX || x < 0) || (y > maxY || y < 0);
	}
}
