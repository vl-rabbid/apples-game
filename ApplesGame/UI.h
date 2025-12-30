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

	void UpdateHUD(UI& uI, const Game& game);

	void DrawHUD(UI& uI, sf::RenderWindow& window);

	void UpdateMenu(UI& uI);

	void DrawMenu(UI& uI, sf::RenderWindow& window);

	void UpdateTextAndPosition(sf::Text& text, const std::string string);

	void SetMenuState(UI& uI, const MenuState& menuState);

	MenuEvent GetMenuEvent(UI& uI);

	void MoveMenuUp(UI& uI);

	void MoveMenuDown(UI& uI);
}