#pragma once
#include <SFML/Graphics.hpp>
#include "GameMath.h"

namespace ApplesGame
{
	struct Apple
	{
		bool isEaten = false;
		bool isSpecial = false;
		Position2D position;
		sf::Sprite sprite;
	};

	struct Game;

	void InitApple(Apple& apple, const Game& game);

	void DrawApple(Apple& apple, sf::RenderWindow& window);

	bool IsAppleEaten(Apple& apple);

	void EatApple(Apple& apple);

	bool IsAppleSpecial(Apple& apple);
}
