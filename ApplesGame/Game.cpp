#include "Game.h"
#include <cassert>
#include <SFML/Audio.hpp>

namespace ApplesGame
{
	void PlaySound(Game& game, const sf::SoundBuffer& soundBuffer)
	{
		game.sound.setBuffer(soundBuffer);
		game.sound.play();
	}

	void SetGameState(Game& game, const GameState& gameState)
	{
		game.gameState = gameState;
		switch (game.gameState)
		{
		case GameState::MainMenu:
		{
			SetMenuState(game.uI, MenuState::MainMenu);
			break;
		}
		case GameState::GameLoop:
		{
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
			break;
		}case GameState::GameOver:
		{
			PlaySound(game, game.deathSound);
			SetMenuState(game.uI, MenuState::GameOverMenu);
			break;
		}
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

		SetGameState(game, GameState::MainMenu);
	}

	void HandleImput(Game& game, const sf::Event& event, sf::RenderWindow& window)
	{
		switch (game.gameState)
		{
		case GameState::MainMenu:
		{
			HandleMenuImput(game, event, window);
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
			HandleMenuImput(game, event, window);
			break;
		}
		};
	}

	void UpdateGame(Game& game, const float deltaTime, const float currentTime)
	{
		switch (game.gameState)
		{
		case GameState::MainMenu:
		{
			UpdateUI(game.uI, game, currentTime);
			break;
		}
		case GameState::GameLoop:
		{
			UpdateGameLoop(game, deltaTime);
			UpdateUI(game.uI, game, currentTime);
			break;
		}
		case GameState::GameOver:
		{
			UpdateUI(game.uI, game, currentTime);
			break;
		}
		}
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		switch (game.gameState)
		{
		case GameState::MainMenu:
		{
			DrawUI(game.uI, window, game);
			break;
		}
		case GameState::GameLoop:
		{
			DrawGameLoop(game, window);
			DrawUI(game.uI, window, game);
			break;
		}
		case GameState::GameOver:
		{
			DrawGameLoop(game, window);
			DrawUI(game.uI, window, game);
			break;
		}
		}
	}

	void UpdateGameLoop(Game& game, const float deltaTime)
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
			SetGameState(game, GameState::GameOver);
		}

		// Check stone collision
		for (int i = 0; i < NUM_STONES; ++i)
		{
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE }, game.stones[i].position, { STONE_SIZE, STONE_SIZE }))
			{
				SetGameState(game, GameState::GameOver);
			}
		}
	}

	void DrawGameLoop(Game& game, sf::RenderWindow& window)
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
	}

	void HandleMenuImput(Game& game, const sf::Event& event, sf::RenderWindow& window)
	{
		MenuEvent menuEvent = MenuEvent::Nothing;

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
		{
			MoveMenuUp(game.uI);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
		{
			MoveMenuDown(game.uI);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
		{
			menuEvent = SelectMenuItem(game.uI);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			menuEvent = SelectMenuItem(game.uI);
		}

		if (menuEvent == MenuEvent::StartGame)
		{
			SetGameState(game, GameState::GameLoop);
		}
		else if (menuEvent == MenuEvent::ExitGame)
		{
			window.close();
		}
		else if (menuEvent == MenuEvent::BackMainMenu)
		{
			SetGameState(game, GameState::MainMenu);
		}
	}

	void DeinitializeGame(Game& game)
	{

	}
}