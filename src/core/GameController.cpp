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
#include "GameController.h"
#include "RandomNumberGenerator.h"
#include "SnakeComponent.h"
#include "Utilities.h"

namespace Snake
{
	GameController::GameController(sf::RenderWindow& window) 
		: _screen(window)
		, _scale(5)
	{}
   
	Food GetNextFood(const sf::RenderWindow& window, const SnakeComponent& snake)
	{
		sf::Vector2f point;
		while (true)
		{
			point = sf::Vector2f(GetRandomNumber(0, window.getSize().x - 4 * BoxSize), GetRandomNumber(0, window.getSize().y - 4 * BoxSize));
			auto rect = BuildRectangleShape(point, sf::Color::Black);
			if (!snake.OverlapsRectangle(rect)) 
			{
				break;
			}
		}

		return Food(point);
	}

	void GameController::Run()
	{
		_screen.setFramerateLimit(15);

		const auto x = GetRandomNumber(_screen.getSize().x / 4, _screen.getSize().x * 3 / 4);
		const auto y = GetRandomNumber(_screen.getSize().y / 4, _screen.getSize().y * 3 / 4);

		auto direction = Direction::Right;
		SnakeComponent snake(x, y, direction, sf::Color::Green, sf::Color::Yellow);
		auto food = GetNextFood(_screen, snake);
		while (true)
		{
			_screen.clear();
			snake.Draw(_screen);
			_screen.draw(food.GetRectangle());

			sf::Event event;
			while (_screen.pollEvent(event))
			{
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Up && direction != Direction::Down)
					{
						direction = Direction::Up;
					}
					else if (event.key.code == sf::Keyboard::Down && direction != Direction::Up)
					{
						direction = Direction::Down;
					}
					else if (event.key.code == sf::Keyboard::Left && direction != Direction::Right)
					{
						direction = Direction::Left;
					}
					else if (event.key.code == sf::Keyboard::Right && direction != Direction::Left)
					{
						direction = Direction::Right;
					}
				}

				if (event.type == sf::Event::Closed)
				{
					exit(0);
				}
			}

			if (snake.DoesSnakeCrossItself() || snake.DoesSnakeLeaveWindow(_screen.getSize().x, _screen.getSize().y))
			{
				break;
			}

			const auto snakeAte = snake.OverlapsRectangle(food.GetRectangle());
			snake.NextDirection(direction, snakeAte);

			if (snakeAte)
			{
				food = GetNextFood(_screen, snake);
			}

			_screen.display();
		}
	}
}
