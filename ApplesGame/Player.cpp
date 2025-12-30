#include "Player.h"
#include "Constants.h"
#include "Game.h"
#include "Math.h"
#include "Apple.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const Game& game)
	{
		// Init player vars
		player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Right;

		// Init player sprite
		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		UpdatePlayerSprite(player);
		player.sprite.setPosition(player.position.x, player.position.y);
		window.draw(player.sprite);
	}

	void HandlePlayerMovementInput(Player& player, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
		{
			player.direction = PlayerDirection::Right;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
		{
			player.direction = PlayerDirection::Up;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			player.direction = PlayerDirection::Left;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
		{
			player.direction = PlayerDirection::Down;
		}
	}

	void UpdatePlayerSprite(Player& player)
	{
		sf::Vector2f playerScale;
		playerScale.x = abs(player.sprite.getScale().x);
		playerScale.y = abs(player.sprite.getScale().y);
		switch (player.direction)
		{
		case PlayerDirection::Right:
		{
			player.sprite.setScale(playerScale.x, playerScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		case PlayerDirection::Up:
		{
			player.sprite.setScale(playerScale.x, playerScale.y);
			player.sprite.setRotation(270.f);
			break;
		}
		case PlayerDirection::Left:
		{
			player.sprite.setScale(-playerScale.x, playerScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		case PlayerDirection::Down:
		{
			player.sprite.setScale(playerScale.x, playerScale.y);
			player.sprite.setRotation(90.f);
			break;
		}
		}
	}

	void UpdatePlayerPosition(Player& player, const float deltaTime)
	{
		switch (player.direction)
		{
		case PlayerDirection::Right:
		{
			player.position.x += player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			player.position.y -= player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			player.position.x -= player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			player.position.y += player.speed * deltaTime;
			break;
		}
		}
	}
	bool HasPlayerCollidedWithScreenBorder(Player& player)
	{
		return ((player.position.x + PLAYER_SIZE / 2.f) > SCREEN_WIDTH) || ((player.position.x - PLAYER_SIZE / 2.f) < 0.f) ||
			((player.position.y + PLAYER_SIZE / 2.f) > SCREEN_HEIGHT) || ((player.position.y - PLAYER_SIZE / 2.f) < 0.f);
	}
}
