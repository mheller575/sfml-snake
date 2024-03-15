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

namespace Snake
{
	GameController::GameController(sf::RenderWindow * w) 
		: _snake(w)
		, _screen(w)
		, _score(0)
		, _scale(5)
	{}
   
	void GameController::Start()
	{
		LoadResources();
		GameLoop();
	}
   
	void GameController::GameLoop()
	{
		_screen->setFramerateLimit(60);
		bool loopInvarient = true;
		sf::Vector2<int> direction(-1,0);
		Food food(_snake.GetNextFoodLocation());
		while (loopInvarient) 
		{
			SetupScene();
			_screen->draw(food.GetRectangle());
			sf::Event event;
			while (_screen->pollEvent(event)) 
			{
				if (event.type == sf::Event::KeyReleased) 
				{
					if (event.key.code == sf::Keyboard::Up) 
					{
						direction.y = -1;
						direction.x = 0;
					} 
					else if (event.key.code == sf::Keyboard::Down) 
					{
						direction.y = 1;
						direction.x = 0;
					}
					else if (event.key.code == sf::Keyboard::Left) 
					{
						direction.x = -1;
						direction.y = 0;
					}
					else if (event.key.code == sf::Keyboard::Right) 
					{
						direction.x = 1;
						direction.y = 0;
					}
				}

				if (event.type == sf::Event::Closed) 
				{
					exit(0);
				}
			}

			_snake.ChangeDirection(direction);

			if (_snake.Died()) 
			{
				//game over
				loopInvarient = false;
			}

			if (_snake.AteFood(&food))
			{
				_score++;
				food = Food(_snake.GetNextFoodLocation());
			}

			_screen->display();
		}
	}

	void GameController::SetupScene()
	{
		_screen->clear();
		_snake.Draw();
	}

	void GameController::LoadResources()
	{
		//TODO: Implement
	}

	sf::Font* GameController::GetFont(Fonts font)
	{
		return &fontList[font];
	}
}
