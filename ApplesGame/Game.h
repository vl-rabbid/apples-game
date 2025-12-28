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
		Welcome = 0,
		GameLoop,
		GameOver
	};

	struct Game
	{
		// Global game data
		GameState gameState = GameState::Welcome;
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

	void PlaySound(Game& game, sf::SoundBuffer& soundBuffer);

	void RestartGame(Game& game);

	void InitGame(Game& game);

	void HandleImput(Game& game);

	void UpdateGame(Game& game, float deltaTime, float currentTime);

	void DrawGame(Game& game, sf::RenderWindow& window);

	void DeinitializeGame(Game& game);
}