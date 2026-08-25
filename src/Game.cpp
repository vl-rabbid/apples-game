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
			UpdatePlayerScore(game);
			LoadLeaderboard(game.uI, game);
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
			UpdateMenu(game.uI, game, deltaTime);
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
			UpdateMenu(game.uI, game, deltaTime);
			break;
		}
		case GameState::GameOver:
		{
			UpdateMenu(game.uI, game, deltaTime);
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
		assert(game.playerTexture.loadFromFile(std::string(RESOURCES_PATH) + "/Player.png"));
		assert(game.appleTexture.loadFromFile(std::string(RESOURCES_PATH) + "/Apple.png"));
		assert(game.stoneTexture.loadFromFile(std::string(RESOURCES_PATH) + "/Rock.png"));

		// Load sounds
		assert(game.appleEatSound.loadFromFile(std::string(RESOURCES_PATH) + "/AppleEat.wav"));
		assert(game.deathSound.loadFromFile(std::string(RESOURCES_PATH) + "/Death.wav"));

		// Load font 
		assert(game.font.loadFromFile(std::string(RESOURCES_PATH) + "/Fonts/Roboto-Regular.ttf"));

		// Init leaderboard
		game.leaderboard.clear();
		game.leaderboard["Alice"] = GetRandomInt(1000, 5000);
		game.leaderboard["Bob"] = GetRandomInt(1000, 5000);
		game.leaderboard["Carol"] = GetRandomInt(1000, 5000);
		game.leaderboard["Dave"] = GetRandomInt(1000, 5000);
		game.leaderboard["John"] = GetRandomInt(1000, 5000);

		InitGameMode(game.gameMode);
		InitUI(game.uI, game);
		game.sound.setVolume(25.f);
		SetGameState(game, GameState::MainMenu);
	}

	void StartGameLoop(Game& game)
	{
		game.playerScore = 0;
		InitPlayer(game.player, game);

		game.apples.clear();
		game.apples.resize(GetNumberOfApples(game.gameMode));
		for (size_t i = 0; i < game.apples.size(); ++i) 
		{
			InitApple(game.apples[i], game);
		}

		game.stones.clear();
		game.stones.resize(GetNumberOfStones(game.gameMode));
		for (size_t i = 0; i < game.stones.size(); ++i) 
		{
			InitStone(game.stones[i], game);
		}
	}

	void UpdateGameLoop(Game& game, const float deltaTime)
	{
		UpdatePlayerPosition(game.player, deltaTime);

		// Check eaten apples
		

		for (Apple& apple : game.apples)
		{
			if (HasPlayerCollidedWithApple(game.player, apple))
			{
				if (!IsAppleEaten(apple))
				{
					PlaySound(game, game.appleEatSound);
					
					if (IsAppleSpecial(apple))
					{
						game.playerScore += (unsigned int)(2.f * (float)POINTS_FOR_APPLE * GetScoreMultiplier(game.gameMode));
					}
					else
					{
						game.playerScore += (unsigned int)((float)POINTS_FOR_APPLE * GetScoreMultiplier(game.gameMode));
					}

					if (IsGameModeFlagOn(game.gameMode, GameModeFlag::AcceleratePlayer) && !(IsAppleSpecial(apple)))
					{
						game.player.speed += ACCELERATION;
					}
					if (IsGameModeFlagOn(game.gameMode, GameModeFlag::InfiniteApples))
					{
						InitApple(apple, game);
					}
					else
					{
						EatApple(apple);
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
		for (Stone& stone : game.stones)
		{
			if (HasPlayerCollidedWithStone(game.player, stone))
			{
				SetGameState(game, GameState::GameOver);
			}
		}
	}

	void DrawGameLoop(Game& game, sf::RenderWindow& window)
	{
		for (Stone& stone : game.stones)
		{
			DrawStone(stone, window);
		}
		for (Apple& apple : game.apples)
		{
			DrawApple(apple, window);
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
		case MenuItemType::Leaderboard:
		{
			SetMenuState(game.uI, MenuState::LeaderboardMenu);
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

	void DeinitializeGame(Game& game, sf::RenderWindow& window)
	{
		window.close();
	}

	void UpdatePlayerScore(Game& game)
	{
		auto entry = game.leaderboard.find(PLAYER_NAME);
		if (entry != game.leaderboard.end())
		{
			if (game.playerScore > entry->second)
			{
				entry->second = game.playerScore;
				game.uI.showNewRecordText = true;
			}
		}
		else
		{
			game.leaderboard[PLAYER_NAME] = game.playerScore;
			game.uI.showNewRecordText = true;
		}
	}
}
