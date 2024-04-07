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

#include "MainMenu.h"

#include "core/GameController.h"
#include "core/RandomNumberGenerator.h"

namespace Snake
{
	MainMenu::MainMenu(sf::RenderWindow& w)
		: _window(w)
		, _main_menu_context(nullptr, menu_destroy_context)
		, _commonMenuStyle(game_menu::Style
			{
				.TitleFont = &_font,
				.ItemFont = &_font,
				.TitleFontSize = 36,
				.ItemFontSize = 24,
				.MenuTitleScaleFactor = 1,
				.MenuItemScaleFactor = 1.5,
				.colorScheme =
				{
					.titleColor = 0xFFFFFF,
					.itemColor = 0xFFFFFF,
					.selectedColor = 0xFF22F1
				},
				.PaddingTitle =
				{
					.top = 100,
					.left = 0,
				},
				.PaddingItems =
				{
					.top = 40,
				},
				.TitleAlign = game_menu::Align::Center,
				.ItemAlign = game_menu::Align::Center
			})
	{
		StartMenuContext();
		_window.setFramerateLimit(60);
	}

	void MainMenu::Start()
	{
		while (_window.isOpen())
		{
			if (_is_exit_requested)
			{
				_window.close();
				break;
			}

			sf::Event event;
			while (_window.pollEvent(event)) 
			{
				if (event.type == sf::Event::Closed) 
				{
					_is_exit_requested = true;
					break;
				}

				menu_handle_event(_current_menu, event);
			}

			_window.clear();
			menu_render(_current_menu);
			_window.display();
		}
	}

	void MainMenu::StartMenuContext()
	{
		_font.loadFromFile("sansation.ttf");

		std::vector<game_menu::MenuItem> items
		{
			{
				"New Game",
				[&](sf::RenderTarget& target) 
				{
					const auto windowMaxX = _window.getSize().x;
					const auto windowMaxY = _window.getSize().y;

					const auto foodX = GetRandomNumber(0, windowMaxX);
					const auto foodY = GetRandomNumber(0, windowMaxY);

					const auto snakeX = GetRandomNumber(0, windowMaxX);
					const auto snakeY = GetRandomNumber(0, windowMaxY);
					
					FoodComponent foodComponent(sf::Vector2f(GetRandomNumber(0, windowMaxX), GetRandomNumber(0, windowMaxY)));
					SnakeComponent snakeComponent(snakeX, snakeY, Direction::Right, sf::Color::Green, sf::Color::Yellow);
					GameBoard gameBoard(snakeComponent, foodComponent, 50000, windowMaxX, windowMaxY);
					GameController gameController(Direction::Right, gameBoard, _window);

					gameController.Run();

					return false;
				}
			},
			{
				"Leaderboard",
				[](sf::RenderTarget& target) {}
			},
			{
				"Settings", 
				[](sf::RenderTarget& target) {}
			},
			{
				"Exit",
				[&](sf::RenderTarget& target) 
				{ 
					this->_is_exit_requested = true; 
				}
			} 
		};

		game_menu::MenuConfig config
		{
			.title = "Snake", 
			.items = items, 
			.style = _commonMenuStyle
		};

		_main_menu_context.reset(create_menu_context(_window, config));
		_current_menu = _main_menu_context.get();
	}
}
