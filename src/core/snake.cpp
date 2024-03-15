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

#include "Food.h"
#include "RandomNumberGenerator.h"
#include "Utilities.h"
#include "Snake.h"
#include "GameController.h"

namespace Snake
{
	bool IsFoodInSnake(const sf::Vector2f& foodPoint, const std::vector<sf::RectangleShape>& snake);

	Snake::Snake(sf::RenderWindow* w)
		: _colorBody(sf::Color::Green)
		, _colorHead(sf::Color::Yellow)
		, _movementScale(5)
		, _screen(w)
		, _snakeLength(1)
		, _updateLength(false)
	{
		const auto x = GetRandomNumber(_screen->getSize().x / 4, _screen->getSize().x * 3 / 4);
		const auto y = GetRandomNumber(_screen->getSize().y / 4, _screen->getSize().y * 3 / 4);
		_body.push_back(BuildRectangleShape(sf::Vector2f(x, y), _colorHead));
		_snakeDirectionList.push_front(sf::Vector2<int>(-1, 0));
	}

	void Snake::Draw()
	{
		for (auto i = _body.rbegin(); i != _body.rend(); ++i)
		{
			_screen->draw(*i);
		}
	}

	bool Snake::Died()
	{
		// hitting walls check
		int x = _body[0].getGlobalBounds().left;
		int y = _body[0].getGlobalBounds().top;
		int mx = _screen->getSize().x;
		int my = _screen->getSize().y;
		return (x > mx || x < 0) || (y > my || y < 0);
	}

	bool Snake::AteFood(Food* fd)
	{
		if (_updateLength) 
		{
			_snakeLength++;
			_updateLength = false;
		}

		if (DoRectanglesOverlap(_body[0], fd->GetRectangle())) 
		{
			_updateLength = true;
			sf::Vector2f new_location = _body[_body.size() - 1].getPosition();
			_body.push_back(BuildRectangleShape(new_location, _colorBody));
			_snakeDirectionList.push_back(_snakeDirectionList.back());
			return true;
		}

		return false;
	}

	void Snake::ChangeDirection(sf::Vector2<int> direction)
	{
		_snakeDirectionList.push_front(direction);
		_snakeDirectionList.pop_back();

		std::list<sf::Vector2<int>>::iterator i = _snakeDirectionList.begin();
		int index = 0;
		while (i != _snakeDirectionList.end() && index < _snakeLength) 
		{
			_body[index].move(_movementScale * (*i).x, _movementScale * (*i).y);
			index++;
			i++;
		}
	}

	sf::Vector2f Snake::GetNextFoodLocation()
	{
		sf::Vector2f foodPoint;
		do
		{
			const auto x = GetRandomNumber(0, _screen->getSize().x - 4 * BoxSize);
			const auto y = GetRandomNumber(0, _screen->getSize().y - 4 * BoxSize);

			foodPoint = sf::Vector2f(x, y);
		} 
		while (IsFoodInSnake(foodPoint, _body));

		return foodPoint;
	}

	bool IsFoodInSnake(const sf::Vector2f& foodPoint, const std::vector<sf::RectangleShape>& snake)
	{
		for (const auto& segment : snake)
		{
			if (segment.getGlobalBounds().contains(foodPoint))
			{
				return true;
			}
		}

		return false;
	}
}
