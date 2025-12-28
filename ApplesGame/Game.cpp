#include "Game.h"
#include <cassert>
#include <SFML/Audio.hpp>

namespace ApplesGame
{
	void PlaySound(Game& game, sf::SoundBuffer& soundBuffer)
	{
		game.sound.setBuffer(soundBuffer);
		game.sound.play();
	}

	void RestartGame(Game& game)
	{
		game.gameState = GameState::GameLoop;
		game.numEatenApples = 0;

		InitPlayer(game.player, game);
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			InitApple(game.apples[i], game);
		}
		for (int i = 0; i < NUM_STONES; ++i)
		{
			InitStone(game.stones[i], game);
		}
	}

	void InitGame(Game& game)
	{
		// Load textures
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.stoneTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));

		// Load sounds
		assert(game.appleEatSound.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		assert(game.deathSound.loadFromFile(RESOURCES_PATH + "\\Death.wav"));

		// Load font 
		assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts/Roboto-Regular.ttf"));

		InitUI(game.uI, game);
		game.sound.setVolume(25.f);
		game.gameState = GameState::Welcome;
	}

	void HandleImput(Game& game)
	{
		switch (game.gameState)
		{
		case GameState::Welcome:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				RestartGame(game);
			}
			break;
		}
		case GameState::GameLoop:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				game.player.direction = PlayerDirection::Right;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				game.player.direction = PlayerDirection::Up;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				game.player.direction = PlayerDirection::Left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				game.player.direction = PlayerDirection::Down;
			}
			break;
		}
		case GameState::GameOver:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				RestartGame(game);
			}
			break;
		}
		};
	}

	void UpdateGame(Game& game, float deltaTime, float currentTime)
	{
		switch (game.gameState)
		{
		case GameState::Welcome:
		{
			break;
		}
		case GameState::GameLoop:
		{
			UpdatePlayerPosition(game.player, deltaTime);

			// Check eaten apples 
			for (int i = 0; i < NUM_APPLES; ++i)
			{
				if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.0, game.apples[i].position, APPLE_SIZE / 2.0))
				{
					PlaySound(game, game.appleEatSound);
					InitApple(game.apples[i], game);

					game.numEatenApples++;
					game.player.speed += ACCELERATION;
				}
			}

			// Check border collision
			if (HasPlayerCollidedWithScreenBorder(game.player))
			{
				PlaySound(game, game.deathSound);
				game.gameState = GameState::GameOver;
			}

			// Check stone collision
			for (int i = 0; i < NUM_STONES; ++i)
			{
				if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE }, game.stones[i].position, { STONE_SIZE, STONE_SIZE }))
				{
					PlaySound(game, game.deathSound);
					game.gameState = GameState::GameOver;
				}
			}
			break;
		}
		case GameState::GameOver:
		{
			break;
		}
		}
		UpdateUI(game.uI, game, currentTime);
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		for (int i = 0; i < NUM_STONES; ++i)
		{
			DrawStone(game.stones[i], window);
		}
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			DrawApple(game.apples[i], window);
		}
		DrawPlayer(game.player, window);
		DrawUI(game.uI, window, game);
	}

	void DeinitializeGame(Game& game)
	{

	}
}