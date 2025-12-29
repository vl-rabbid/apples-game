#include "UI.h"
#include "Game.h"
#include "Math.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace ApplesGame
{
	void InitUI(UI& uI, const Game& game)
	{
		// Init Menu Title
		uI.title.setString("Apples Game!");
		uI.title.setFont(game.font);
		uI.title.setStyle(sf::Text::Bold);
		uI.title.setCharacterSize(90);
		uI.title.setFillColor(sf::Color::Yellow);
		SetTextRelativeOrigin(uI.title, 0.5f, 0.5f);
		SetTextScreenRelativePosition(uI.title, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 0.2f);

		// Init Menu Items
		for (int i = 0; i < NUM_MENU_ITEMS; i++)
		{
			uI.menuItems[i].text.setString("Item " + std::to_string(i));
			uI.menuItems[i].text.setFont(game.font);
			uI.menuItems[i].text.setCharacterSize(40);
			uI.menuItems[i].text.setFillColor(sf::Color::Yellow);
			SetTextRelativeOrigin(uI.menuItems[i].text, 0.5f, 0.5f);
			SetTextScreenRelativePosition(uI.menuItems[i].text, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 0.4f);
			ShiftTextPozition(uI.menuItems[i].text, 0.f, 60.f * i);
		}

		// Init Score
		uI.score.setString("Apples Eaten:");
		uI.score.setFont(game.font);
		uI.score.setCharacterSize(20);
		uI.score.setFillColor(sf::Color::Yellow);
		SetTextRelativeOrigin(uI.score, 0.f, 0.f);
		SetTextScreenRelativePosition(uI.score, SCREEN_WIDTH, SCREEN_HEIGHT, 0.01f, 0.01f);

		//Init tint
		uI.tint.setFillColor(sf::Color(0, 0, 0, 180));
		uI.tint.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	}

	void UpdateUI(UI& uI, const Game& game, const float currentTime)
	{
		switch(game.gameState)
		{
		case GameState::MainMenu:
		{
			UpdateMenu(uI);
			break;
		}
		case GameState::GameLoop:
		{
			UpdateTextAndPosition(uI.score, "Apples Eaten: " + std::to_string(game.numEatenApples));
			break;
		}
		case GameState::GameOver:
		{
			UpdateMenu(uI);
			break;
		}
		};
	}

	void DrawUI(UI& uI, sf::RenderWindow& window, const Game& game)
	{
		switch (game.gameState)
		{
		case GameState::MainMenu:
		{
			window.draw(uI.title);
			for (int i = 0; i < NUM_MENU_ITEMS; i++)
			{
				if (uI.menuItems[i].isActive)
				{
					window.draw(uI.menuItems[i].text);
				}
			}
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
			for (int i = 0; i < NUM_MENU_ITEMS; i++)
			{
				if (uI.menuItems[i].isActive)
				{
					window.draw(uI.menuItems[i].text);
				}
			}
			break;
		}
		};
	}

	void UpdateTextAndPosition(sf::Text& text, const std::string string)
	{
		Vector2D relativePosition = GetTextScreenRelativePosition(text, SCREEN_WIDTH, SCREEN_HEIGHT);
		Vector2D relativeOrigin = GetTextRelativeOrigin(text);
		text.setString(string);
		SetTextRelativeOrigin(text, relativeOrigin.x, relativeOrigin.y);
		SetTextScreenRelativePosition(text, SCREEN_WIDTH, SCREEN_HEIGHT, relativePosition.x, relativePosition.y);
	}

	void SetMenuState(UI& uI, const MenuState& menuState)
	{
		uI.menuState = menuState;
		uI.menuSelectedItem = 0;
		UpdateMenu(uI);
	}

	void UpdateMenu(UI& uI)
	{
		for (int i = 0; i < NUM_MENU_ITEMS; i++)
		{
			uI.menuItems[i].isActive = false;
			uI.menuItems[i].text.setFillColor(sf::Color::Yellow);
		}
		uI.menuSelectedItem = uI.menuSelectedItem % NUM_MENU_ITEMS;
		uI.menuItems[uI.menuSelectedItem].text.setFillColor(sf::Color::Red);

		switch (uI.menuState)
		{
		case MenuState::MainMenu:
		{
			UpdateTextAndPosition(uI.title, "Apples Game!");
			SetMenuItem(uI.menuItems[0], "Start game", MenuEvent::StartGame);
			SetMenuItem(uI.menuItems[1], "Exit game", MenuEvent::ExitGame);
			break;
		}
		case MenuState::GameOverMenu:
		{
			UpdateTextAndPosition(uI.title, "GAME OVER");
			SetMenuItem(uI.menuItems[0], "Restart game", MenuEvent::StartGame);
			SetMenuItem(uI.menuItems[1], "Back to main menu", MenuEvent::BackMainMenu);
			SetMenuItem(uI.menuItems[2], "Exit game", MenuEvent::ExitGame);
			break;
		}
		}
	}

	MenuEvent SelectMenuItem(UI& uI)
	{
		uI.menuSelectedItem = uI.menuSelectedItem % NUM_MENU_ITEMS;
		return uI.menuItems[uI.menuSelectedItem].event;
	}

	void MoveMenuUp(UI& uI)
	{
		do {
			uI.menuSelectedItem = (uI.menuSelectedItem - 1 + NUM_MENU_ITEMS) % NUM_MENU_ITEMS;
		} while (!uI.menuItems[uI.menuSelectedItem].isActive);
	}

	void MoveMenuDown(UI& uI)
	{
		do {
			uI.menuSelectedItem = (uI.menuSelectedItem + 1) % NUM_MENU_ITEMS;
		} while (!uI.menuItems[uI.menuSelectedItem].isActive);
	}
}


