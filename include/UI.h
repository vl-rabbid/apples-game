#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Menu.h"

namespace ApplesGame
{
	struct UI
	{
		// HUD
		sf::Text playerScore;

		// Menus
		sf::Text title;
		sf::Text note;
		size_t menuSelectedItem = 0;
		MenuState menuState{};
		std::vector<MenuItem> menuItems;
		sf::RectangleShape tint;

		// Leaderboard
		bool showLeaderboard = false;
		std::vector<sf::Text> leaderboardItems;
		bool showNewRecordText = false;
		sf::Text newRecord;
	};

	struct Game;

	void InitUI(UI& uI, const Game& game);

	void UpdateHUD(UI& uI, const Game& game);

	void DrawHUD(UI& uI, sf::RenderWindow& window);

	void UpdateMenu(UI& uI, const Game& game, const float deltaTime);

	void LoadNewMenu(UI& uI);

	void DrawMenu(UI& uI, sf::RenderWindow& window);

	void UpdateTextAndPosition(sf::Text& text, const std::string string);

	void SetMenuState(UI& uI, const MenuState& menuState);

	MenuItemType GetMenuItemType(UI& uI);

	void MoveMenuUp(UI& uI);

	void MoveMenuDown(UI& uI);

	void SetMenuItemsPosition(UI& uI, float shiftX, float shiftY);

	void LoadLeaderboard(UI& uI, const Game& game);

	void UpdateBlinkText(sf::Text& text, const float blinkInterval, const float deltaTime);
}