#pragma once
#include <SFML/Graphics.hpp>
#include "GameMath.h"

namespace ApplesGame
{
	struct Stone
	{
		Position2D position;
		sf::Sprite sprite;
	};

	struct Game;

	void InitStone(Stone& stone, const Game& game);

	void DrawStone(Stone& stone, sf::RenderWindow& window);
}