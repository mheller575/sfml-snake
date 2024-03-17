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

#include <chrono>

#include "GameBoard.h"
#include "RandomNumberGenerator.h"
#include "Utilities.h"

namespace Snake
{
	static FoodComponent GetNextFood(const std::int32_t& maxWindowX, const std::int32_t& maxWindowY, const SnakeComponent& snake)
	{
		sf::Vector2f point;
		while (true)
		{
			point = sf::Vector2f(GetRandomNumber(0, maxWindowX - 4 * BoxSize), GetRandomNumber(0, maxWindowY - 4 * BoxSize));
			auto rect = BuildRectangleShape(point, sf::Color::Black);
			if (!snake.OverlapsRectangle(rect))
			{
				break;
			}
		}

		return FoodComponent(point);
	}

	GameBoard::GameBoard(const SnakeComponent& snakeComponent, const FoodComponent& foodComponent, const std::int64_t& updateRateUs, 
		const std::int32_t& maxWindowX, const std::int32_t& maxWindowY)
		: _snake(snakeComponent)
		, _food(foodComponent)
		, _updateRateUs(updateRateUs)
		, _maxWindowX(maxWindowX)
		, _maxWindowY(maxWindowY)
	{}

	void GameBoard::Draw(sf::RenderWindow& window) const
	{
		_snake.Draw(window);
		_food.Draw(window);
	}

	bool GameBoard::Run(const std::optional<Direction>& direction)
	{
		const auto currentTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		if (currentTimeUs - _lastTimeUs > _updateRateUs)
		{
			_lastTimeUs = currentTimeUs;

			auto snakeAte = _snake.OverlapsRectangle(_food.GetShape());
			_snake.NextDirection(direction, snakeAte);
			if (snakeAte)
			{
				_food = GetNextFood(_maxWindowX, _maxWindowY, _snake);
			}

			if (_snake.DoesSnakeCrossItself() || _snake.DoesSnakeLeaveWindow(_maxWindowX, _maxWindowY))
			{
				return false; // Snake died, return false alerting caller.
			}
		}

		return true;
	}
}
