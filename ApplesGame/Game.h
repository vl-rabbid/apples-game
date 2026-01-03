#pragma once
#include "Player.h"
#include "Apple.h"
#include "Stone.h"
#include "Constants.h"
#include "UI.h"
#include "Math.h"
#include "GameMode.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace ApplesGame
{
	enum class GameState
	{
		MainMenu = 0,
		GameLoop,
		Pause,
		GameOver,
		ExitGame
	};

	struct Game
	{
		// Global game data
		GameState gameState{};
		uint16_t gameMode = 0;
		unsigned int score = 0;

		//Resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;
		sf::SoundBuffer appleEatSound;
		sf::SoundBuffer deathSound;

		Player player;
		Apple* apples = nullptr;
		Stone* stones = nullptr;
		UI uI;
		sf::Sound sound;
		sf::Font font;
	};

	bool IsGameRunning(Game& game);

	void PlaySound(Game& game, const sf::SoundBuffer& soundBuffer);

	void SetGameState(Game& game, const GameState& gameState);

	void HandleImputAndEvents(Game& game, const sf::Event& event);

	void UpdateGame(Game& game, const float deltaTime);

	void DrawGame(Game& game, sf::RenderWindow& window);

	void InitGame(Game& game);

	void StartGameLoop(Game& game);

	void UpdateGameLoop(Game& game, const float deltaTime);

	void DrawGameLoop(Game& game, sf::RenderWindow& window);

	void HandleMenuImput(Game& game, const sf::Event& event);

	void SelectMenuItem(Game& game, const MenuItemType& menuItemType);

	void AdjustMenuItem(Game& game, const MenuItemType& menuItemType, const AdjustmentType& adjustmentType);

	void FreeAppleMemoryAllocation(Game& game);

	void FreeStoneMemoryAllocation(Game& game);

	void DeinitializeGame(Game& game, sf::RenderWindow& window);
}