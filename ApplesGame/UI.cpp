#include "UI.h"
#include "Game.h"
#include "Math.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace ApplesGame
{
	void InitUI(UI& uI, Game& game)
	{
		// Init Title
		uI.title.setString("Apples Game!");
		uI.title.setFont(game.font);
		uI.title.setStyle(sf::Text::Bold);
		uI.title.setCharacterSize(90);
		uI.title.setFillColor(sf::Color::Yellow);
		SetTextRelativeOrigin(uI.title, 0.5f, 0.5f);
		SetTextScreenRelativePosition(uI.title, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 0.2f);

		// Init Under title
		uI.underTitle.setString("Use Arrows to control");
		uI.underTitle.setFont(game.font);
		uI.underTitle.setCharacterSize(25);
		uI.underTitle.setFillColor(sf::Color::Yellow);
		SetTextRelativeOrigin(uI.underTitle, 0.5f, 0.5f);
		SetTextScreenRelativePosition(uI.underTitle, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 0.4f);

		//Hello
		// Init Score
		uI.score.setString("Apples Eaten:");
		uI.score.setFont(game.font);
		uI.score.setCharacterSize(20);
		uI.score.setFillColor(sf::Color::Yellow);
		SetTextRelativeOrigin(uI.score, 0.f, 0.f);
		SetTextScreenRelativePosition(uI.score, SCREEN_WIDTH, SCREEN_HEIGHT, 0.01f, 0.01f);

		// Init Call to action
		uI.callToAction.setString("Press SPACE to start");
		uI.callToAction.setFont(game.font);
		uI.callToAction.setCharacterSize(30);
		uI.callToAction.setFillColor(sf::Color::Yellow);
		SetTextRelativeOrigin(uI.callToAction, 0.5f, 0.5f);
		SetTextScreenRelativePosition(uI.callToAction, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 0.7f);

		//Init tint
		uI.tint.setFillColor(sf::Color(0, 0, 0, 180));
		uI.tint.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	}

	void UpdateUI(UI& uI, const Game& game, float currentTime)
	{
		switch(game.gameState)
		{
		case GameState::Welcome:
		{
			UpdateTextAndPosition(uI.title, "Apples Game!");
			UpdateTextAndPosition(uI.underTitle, "Use Arrows to control, eat apples, avoid stones and borders");
			UpdateTextAndPosition(uI.callToAction, "Press SPACE to start");

			if ((int)currentTime % 2 == 0)
			{
				uI.callToAction.setFillColor(sf::Color::Yellow);
			}
			else
			{
				uI.callToAction.setFillColor(sf::Color::Red);
			}
			break;
		}
		case GameState::GameLoop:
		{
			UpdateTextAndPosition(uI.score, "Apples Eaten: " + std::to_string(game.numEatenApples));
			break;
		}
		case GameState::GameOver:
		{
			UpdateTextAndPosition(uI.title, "GAME OVER");
			UpdateTextAndPosition(uI.underTitle, "Final score: " + std::to_string(game.numEatenApples));
			UpdateTextAndPosition(uI.callToAction, "Press SPACE to restart");
			if ((int)currentTime % 2 == 0)
			{
				uI.callToAction.setFillColor(sf::Color::Yellow);
			}
			else
			{
				uI.callToAction.setFillColor(sf::Color::Red);
			}
			break;
		}
		};
	}

	void DrawUI(UI& uI, sf::RenderWindow& window, const Game& game)
	{
		switch (game.gameState)
		{
		case GameState::Welcome:
		{
			window.draw(uI.title);
			window.draw(uI.underTitle);
			window.draw(uI.callToAction);
			break;
		}
		case GameState::GameLoop:
		{
			window.draw(uI.score);
			break;
		}
		case GameState::GameOver:
		{
			window.draw(uI.tint);
			window.draw(uI.title);
			window.draw(uI.underTitle);
			window.draw(uI.callToAction);
			break;
		}
		};
	}

	void UpdateTextAndPosition(sf::Text& text, std::string string)
	{
		Vector2D relativePosition = GetTextScreenRelativePosition(text, SCREEN_WIDTH, SCREEN_HEIGHT);
		Vector2D relativeOrigin = GetTextRelativeOrigin(text);
		text.setString(string);
		SetTextRelativeOrigin(text, relativeOrigin.x, relativeOrigin.y);
		SetTextScreenRelativePosition(text, SCREEN_WIDTH, SCREEN_HEIGHT, relativePosition.x, relativePosition.y);
	}
}


