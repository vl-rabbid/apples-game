#include "Game.h"
#include <cassert>
#include <SFML/Audio.hpp>

namespace ApplesGame
{
	bool IsGameRunning(Game& game)
	{
		if (game.gameState == GameState::ExitGame)
		{
			return false;
		}
		return true;
	}

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
			break;
		}
		case GameState::Pause:
		{
			SetMenuState(game.uI, MenuState::PauseMenu);
			break;
		}
		case GameState::GameOver:
		{
			PlaySound(game, game.deathSound);
			SetMenuState(game.uI, MenuState::GameOverMenu);
			break;
		}
		case GameState::ExitGame:
		{
			break;
		}
		}
	}

	void HandleImputAndEvents(Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::Closed)
		{
			SetGameState(game, GameState::ExitGame);
			return;
		}

		switch (game.gameState)
		{
		case GameState::MainMenu:
		{
			HandleMenuImput(game, event);
			break;
		}
		case GameState::GameLoop:
		{
			HandlePlayerMovementInput(game.player, event);
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				SetGameState(game, GameState::Pause);
			}
			break;
		}
		case GameState::Pause:
		{
			HandleMenuImput(game, event);
			break;
		}
		case GameState::GameOver:
		{
			HandleMenuImput(game, event);
			break;
		}
		};
	}

	void UpdateGame(Game& game, const float deltaTime)
	{
		switch (game.gameState)
		{
		case GameState::MainMenu:
		{
			UpdateMenu(game.uI, game);
			break;
		}
		case GameState::GameLoop:
		{
			UpdateGameLoop(game, deltaTime);
			UpdateHUD(game.uI, game);
			break;
		}
		case GameState::Pause:
		{
			UpdateMenu(game.uI, game);
			break;
		}
		case GameState::GameOver:
		{
			UpdateMenu(game.uI, game);
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
			DrawMenu(game.uI, window);
			break;
		}
		case GameState::GameLoop:
		{
			DrawGameLoop(game, window);
			DrawHUD(game.uI, window);
			break;
		}
		case GameState::Pause:
		{
			DrawGameLoop(game, window);
			DrawMenu(game.uI, window);
			break;
		}
		case GameState::GameOver:
		{
			DrawGameLoop(game, window);
			DrawMenu(game.uI, window);
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

	void RestartGame(Game& game)
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

	void HandleMenuImput(Game& game, const sf::Event& event)
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
			menuEvent = GetMenuEvent(game.uI);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			menuEvent = GetMenuEvent(game.uI);
		}

		HandleMenuEvent(game, menuEvent);
	}

	void HandleMenuEvent(Game& game, const MenuEvent& menuEvent)
	{
		switch (menuEvent)
		{
		case MenuEvent::Nothing:
		{
			break;
		}
		case MenuEvent::StartGame:
		{
			SetGameState(game, GameState::GameLoop);
			RestartGame(game);
			break;
		}
		case MenuEvent::ContinueGame:
		{
			SetGameState(game, GameState::GameLoop);
			break;
		}
		case MenuEvent::ExitGame:
		{
			SetGameState(game, GameState::ExitGame);
			break;
		}
		case MenuEvent::BackMainMenu:
		{
			SetGameState(game, GameState::MainMenu);
			break;
		}
		}
	}

	void DeinitializeGame(Game& game, sf::RenderWindow& window)
	{
		window.close();
	}
}