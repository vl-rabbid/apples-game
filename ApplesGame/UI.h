#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Menu.h"

namespace ApplesGame
{
	struct UI
	{
		// HUD
		sf::Text score;
		sf::RectangleShape tint;

		// Menus
		sf::Text title;
		int menuSelectedItem;
		MenuState menuState{};
		MenuItem menuItems[NUM_MENU_ITEMS];
	};

	struct Game;

	void InitUI(UI& uI, const Game& game);

	void UpdateUI(UI& uI, const Game& game, const float currentTime);

	void DrawUI(UI& uI, sf::RenderWindow& window, const Game& game);

	void UpdateTextAndPosition(sf::Text& text, const std::string string);

	void SetMenuState(UI& uI, const MenuState& menuState);

	void UpdateMenu(UI& uI);

	MenuEvent SelectMenuItem(UI& uI);

	void MoveMenuUp(UI& uI);

	void MoveMenuDown(UI& uI);
}