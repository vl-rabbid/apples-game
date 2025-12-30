#pragma once
#include "Player.h"
#include "Apple.h"
#include "Stone.h"
#include "Constants.h"
#include "UI.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace ApplesGame
{
	enum class GameState
	{
		MainMenu = 0,
		GameLoop,
		Pause,
		GameOver
	};

	struct Game
	{
		// Global game data
		GameState gameState = GameState::MainMenu;
		int numEatenApples = 0;

		//Resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;
		sf::SoundBuffer appleEatSound;
		sf::SoundBuffer deathSound;

		Player player;
		Apple apples[NUM_APPLES];
		Stone stones[NUM_STONES];
		UI uI;
		sf::Sound sound;
		sf::Font font;
	};

	void PlaySound(Game& game, const sf::SoundBuffer& soundBuffer);

	void SetGameState(Game& game, const GameState& gameState);

	void HandleImput(Game& game, const sf::Event& event, sf::RenderWindow& window);

	void UpdateGame(Game& game, const float deltaTime, const float currentTime);

	void DrawGame(Game& game, sf::RenderWindow& window);

	void InitGame(Game& game);

	void RestartGame(Game& game);

	void UpdateGameLoop(Game& game, const float deltaTime);

	void DrawGameLoop(Game& game, sf::RenderWindow& window);

	void HandleMenuImput(Game& game, const sf::Event& event, sf::RenderWindow& window);

	void HandleMenuEvent(Game& game, const MenuEvent& menuEvent, sf::RenderWindow& window);

	void DeinitializeGame(Game& game);
}