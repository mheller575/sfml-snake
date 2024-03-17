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

#include "GameController.h"

namespace Snake
{
	GameController::GameController(const Direction& initialDirection, const GameBoard& gameBoard, sf::RenderWindow& window)
		: _screen(window)
		, _initialDirection(initialDirection)
		, _gameBoard(gameBoard)
	{
		_screen.setFramerateLimit(60);
	}

	void GameController::Run()
	{
		auto direction = _initialDirection;
		while (true)
		{
			_screen.clear();
			sf::Event event;
			while (_screen.pollEvent(event))
			{
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Up)
					{
						direction = Direction::Up;
					}
					else if (event.key.code == sf::Keyboard::Down)
					{
						direction = Direction::Down;
					}
					else if (event.key.code == sf::Keyboard::Left)
					{
						direction = Direction::Left;
					}
					else if (event.key.code == sf::Keyboard::Right)
					{
						direction = Direction::Right;
					}
				}
				else if (event.type == sf::Event::Closed)
				{
					exit(0);
				}
			}

			if (!_gameBoard.Run(direction))
			{
				return;
			}

			_gameBoard.Draw(_screen);

			_screen.display();
		}
	}
}
