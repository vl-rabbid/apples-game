#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	enum class MenuItemType
	{
		StartGame = 0,
		ContinueGame,
		ExitGame,
		GameMode,
		BackMainMenu,
		RandomizeGameMode,
		InfiniteApples,
		AcceleratePlayer,
		CollideWithBorders,
		NumberOfApples
	};

	enum class MenuState
	{
		MainMenu = 0,
		GameModeMenu,
		PauseMenu,
		GameOverMenu
	};

	struct MenuItem
	{
		sf::Text text;
		MenuItemType itemType{};
		bool isActive;
	};

	void SetMenuItem(MenuItem& menuItem, std::string textTitle,const MenuItemType& menuItemType);

	void UpdateItemString(MenuItem& menuItem, std::string textTitle);
}