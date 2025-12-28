#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct UI
	{
		sf::RectangleShape tint;
		sf::Text title;
		sf::Text underTitle;
		sf::Text score;
		sf::Text callToAction;
	};

	struct Game;

	void InitUI(UI& uI, Game& game);

	void UpdateUI(UI& uI, const Game& game, float currentTime);

	void DrawUI(UI& uI, sf::RenderWindow& window, const Game& game);

	void UpdateTextAndPosition(sf::Text& text, std::string string);
}