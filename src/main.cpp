#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

int main()
{
	using namespace ApplesGame;
	int seed = (int)time(nullptr);
	srand(seed);

	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();
	
	// Game initialization
	Game game;
	InitGame(game);

	// Main loop
	while (IsGameRunning(game))
	{
		// Reduce framerate to not spam CPU and GPU
		sf::sleep(sf::microseconds(16));

		// Calculate delta time
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			HandleImputAndEvents(game, event);
		}

		UpdateGame(game, deltaTime);

		// Draw game graphics
		window.clear();
		DrawGame(game, window);
		window.display();
	}

	// Deinitialization
	DeinitializeGame(game, window);

	return 0;
}
