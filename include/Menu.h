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
		SpawnSpecialApples,
		NumberOfApples,
		NumberOfStones,
		Leaderboard
	};

	enum class MenuState
	{
		MainMenu = 0,
		GameModeMenu,
		PauseMenu,
		GameOverMenu,
		LeaderboardMenu
	};

	struct MenuItem
	{
		sf::Text text;
		MenuItemType itemType{};
		bool isActive = false;
	};

	void SetMenuItem(MenuItem& menuItem, std::string textTitle,const MenuItemType& menuItemType);

	void UpdateItemString(MenuItem& menuItem, std::string textTitle);
}