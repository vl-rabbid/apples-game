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
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				SetGameState(game, GameState::GameLoop);
			}
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

		game.apples = nullptr;
		InitGameMode(game.gameMode);
		InitUI(game.uI, game);
		game.sound.setVolume(25.f);
		SetGameState(game, GameState::MainMenu);
	}

	void StartGameLoop(Game& game)
	{
		game.numEatenApples = 0;
		InitPlayer(game.player, game);

		FreeAppleMemoryAllocation(game);
		game.apples = new Apple[GetNumberOfApples(game.gameMode)];
		for (Apple* ptrApple = game.apples; ptrApple < game.apples + GetNumberOfApples(game.gameMode); ++ptrApple)
		{
			InitApple(*ptrApple, game);
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
		for (Apple* ptrApple = game.apples; ptrApple < game.apples + GetNumberOfApples(game.gameMode); ++ptrApple)
		{
			if (HasPlayerCollidedWithApple(game.player, *ptrApple))
			{
				if (!IsAppleEaten(*ptrApple))
				{
					PlaySound(game, game.appleEatSound);
					game.numEatenApples++;

					if (IsAcceleratePlayer(game.gameMode))
					{
						game.player.speed += ACCELERATION;
					}
					if (IsInfiniteApples(game.gameMode))
					{
						InitApple(*ptrApple, game);
					}
					else
					{
						EatApple(*ptrApple);
					}
				}
			}
		}

		// Check border collision
		if (HasPlayerCollidedWithScreenBorder(game.player))
		{
			if (IsCollideWithBorders(game.gameMode))
			{
				SetGameState(game, GameState::GameOver);
			}
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
		for (Apple* ptrApple = game.apples; ptrApple < game.apples + GetNumberOfApples(game.gameMode); ++ptrApple)
		{
			DrawApple(*ptrApple, window);
		}
		DrawPlayer(game.player, window);
	}

	void HandleMenuImput(Game& game, const sf::Event& event)
	{
		MenuItemType menuItemType;
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
			menuItemType = GetMenuItemType(game.uI);
			SelectMenuItem(game, menuItemType);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			menuItemType = GetMenuItemType(game.uI);
			SelectMenuItem(game, menuItemType);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			menuItemType = GetMenuItemType(game.uI);
			AdjustMenuItem(game, menuItemType, AdjustmentType::Decrement);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
		{
			menuItemType = GetMenuItemType(game.uI);
			AdjustMenuItem(game, menuItemType, AdjustmentType::Increment);
		}
	}

	void SelectMenuItem(Game& game, const MenuItemType& menuItemType)
	{
		switch (menuItemType)
		{
		case MenuItemType::StartGame:
		{
			SetGameState(game, GameState::GameLoop);
			StartGameLoop(game);
			break;
		}
		case MenuItemType::ContinueGame:
		{
			SetGameState(game, GameState::GameLoop);
			break;
		}
		case MenuItemType::ExitGame:
		{
			SetGameState(game, GameState::ExitGame);
			break;
		}
		case MenuItemType::GameMode:
		{
			SetMenuState(game.uI, MenuState::GameModeMenu);
			break;
		}
		case MenuItemType::BackMainMenu:
		{
			SetGameState(game, GameState::MainMenu);
			break;
		}
		case MenuItemType::RandomizeGameMode:
		{
			RandomizeGameMode(game.gameMode);
			break;
		}
		}
	}

	void AdjustMenuItem(Game& game, const MenuItemType& menuItemType, const AdjustmentType& adjustmentType)
	{
		switch (menuItemType)
		{
		case MenuItemType::InfiniteApples:
		{
			SwitchInfiniteApples(game.gameMode);
			break;
		}
		case MenuItemType::AcceleratePlayer:
		{
			SwitchAcceleratePlayer(game.gameMode);
			break;
		}
		case MenuItemType::CollideWithBorders:
		{
			SwitchCollideWithBorders(game.gameMode);
			break;
		}
		case MenuItemType::NumberOfApples:
		{
			AdjustNumberOfApples(game.gameMode, adjustmentType);
			break;
		}
		}
	}

	void FreeAppleMemoryAllocation(Game& game)
	{
		if (game.apples != nullptr) {
			delete[] game.apples;
			game.apples = nullptr;
		}
	}

	void DeinitializeGame(Game& game, sf::RenderWindow& window)
	{
		FreeAppleMemoryAllocation(game);
		window.close();
	}
}