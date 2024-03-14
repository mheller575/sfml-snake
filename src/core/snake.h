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

#include <SFML/Graphics.hpp>
#include <list>

namespace Snake
{
	class Food;

	constexpr auto SNAKE_MAX_LENGTH = 2000;

	class Snake 
	{
	public:
		Snake(sf::RenderWindow *);
		void Draw();
		bool Died();
		bool AteFood(Food *fd);
		void ChangeDirection(sf::Vector2<int> direction);
		sf::Vector2f GetNextFoodLocation();
		
	private:
		sf::RenderWindow *_screen;

		/* Used to determine whether or not to increment length of snake */
		bool _updateLength;

		/* The rate of movement of snake */
		float _movementScale;

		/* Snake parameters */
		int _snakeLength;
		std::list<sf::Vector2<int>> _snakeDirectionList;
		sf::Vector2<int> _lastDirection;
		std::vector<sf::RectangleShape> _body;

		/* Load from options */
		sf::Color _colorBody;
		sf::Color _colorHead;
	};
}
