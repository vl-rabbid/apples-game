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
		game.stones = nullptr;
		InitGameMode(game.gameMode);
		InitUI(game.uI, game);
		game.sound.setVolume(25.f);
		SetGameState(game, GameState::MainMenu);
	}

	void StartGameLoop(Game& game)
	{
		game.score = 0;
		InitPlayer(game.player, game);

		FreeAppleMemoryAllocation(game);
		game.apples = new Apple[GetNumberOfApples(game.gameMode)];
		for (Apple* ptrApple = game.apples; ptrApple < game.apples + GetNumberOfApples(game.gameMode); ++ptrApple)
		{
			InitApple(*ptrApple, game);
		}

		FreeStoneMemoryAllocation(game);
		game.stones = new Stone[GetNumberOfStones(game.gameMode)];
		for (Stone* ptrStone = game.stones; ptrStone < game.stones + GetNumberOfStones(game.gameMode); ++ptrStone)
		{
			InitStone(*ptrStone, game);
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
					
					if (IsAppleSpecial(*ptrApple))
					{
						game.score += (unsigned int)(2.f * (float)POINTS_FOR_APPLE * GetScoreMultiplier(game.gameMode));
					}
					else
					{
						game.score += (unsigned int)((float)POINTS_FOR_APPLE * GetScoreMultiplier(game.gameMode));
					}

					if (IsGameModeFlagOn(game.gameMode, GameModeFlag::AcceleratePlayer) && !(IsAppleSpecial(*ptrApple)))
					{
						game.player.speed += ACCELERATION;
					}
					if (IsGameModeFlagOn(game.gameMode, GameModeFlag::InfiniteApples))
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
		if (IsGameModeFlagOn(game.gameMode, GameModeFlag::CollideWithBorders))
		{
			if (HasPlayerCollidedWithScreenBorder(game.player))
			{
				SetGameState(game, GameState::GameOver);
			}
		}

		// Check stone collision
		for (Stone* ptrStone = game.stones; ptrStone < game.stones + GetNumberOfStones(game.gameMode); ++ptrStone)
		{
			if (HasPlayerCollidedWithStone(game.player, *ptrStone))
			{
				SetGameState(game, GameState::GameOver);
			}
		}
	}

	void DrawGameLoop(Game& game, sf::RenderWindow& window)
	{
		for (Stone* ptrStone = game.stones; ptrStone < game.stones + GetNumberOfStones(game.gameMode); ++ptrStone)
		{
			DrawStone(*ptrStone, window);
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
			SwitchGameModeFlag(game.gameMode, GameModeFlag::InfiniteApples);
			break;
		}
		case MenuItemType::AcceleratePlayer:
		{
			SwitchGameModeFlag(game.gameMode, GameModeFlag::AcceleratePlayer);
			break;
		}
		case MenuItemType::CollideWithBorders:
		{

			SwitchGameModeFlag(game.gameMode, GameModeFlag::CollideWithBorders);
			break;
		}
		case MenuItemType::SpawnSpecialApples:
		{
			SwitchGameModeFlag(game.gameMode, GameModeFlag::SpawnSpecialApples);
			break;
		}
		case MenuItemType::NumberOfApples:
		{
			AdjustNumberOfApples(game.gameMode, adjustmentType);
			break;
		}
		case MenuItemType::NumberOfStones:
		{
			AdjustNumberOfStones(game.gameMode, adjustmentType);
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

	void FreeStoneMemoryAllocation(Game& game)
	{
		if (game.stones != nullptr) {
			delete[] game.stones;
			game.stones = nullptr;
		}
	}

	void DeinitializeGame(Game& game, sf::RenderWindow& window)
	{
		FreeAppleMemoryAllocation(game);
		FreeStoneMemoryAllocation(game);
		window.close();
	}
}