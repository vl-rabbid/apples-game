#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct Apple
	{
		bool isEaten;
		Position2D position;
		sf::Sprite sprite;
	};

	struct Game;

	void InitApple(Apple& apple, const Game& game);

	void DrawApple(Apple& apple, sf::RenderWindow& window);

	bool IsAppleEaten(Apple& apple);

	void EatApple(Apple& apple);
}
