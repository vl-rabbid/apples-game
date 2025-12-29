#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	enum class MenuEvent
	{
		Nothing = 0,
		StartGame,
		ExitGame,
		BackMainMenu
	};

	enum class MenuState
	{
		MainMenu = 0,
		GameOverMenu
	};

	struct MenuItem
	{
		sf::Text text;
		MenuEvent event{};
		bool isActive;
	};

	void SetMenuItem(MenuItem& menuItem, std::string textTitle,const MenuEvent& menuEvent);
}