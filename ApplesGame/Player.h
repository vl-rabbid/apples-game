#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Math.h"

namespace ApplesGame
{
	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Player
	{
		Position2D position;
		float speed;
		PlayerDirection direction{};
		sf::Sprite sprite;
	};

	struct Game;

	void InitPlayer(Player& player, const Game& game);

	void DrawPlayer(Player& player, sf::RenderWindow& window);

	void HandlePlayerMovementInput(Player& player, const sf::Event& event);

	void UpdatePlayerSprite(Player& player);

	void UpdatePlayerPosition(Player& player, const float deltaTime);

	bool HasPlayerCollidedWithScreenBorder(Player& player);
}