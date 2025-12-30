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
		uI.title.setString("title");
		uI.title.setFont(game.font);
		uI.title.setStyle(sf::Text::Bold);
		uI.title.setCharacterSize(90);
		uI.title.setFillColor(sf::Color::Yellow);
		SetTextRelativeOrigin(uI.title, 0.5f, 0.5f);
		SetTextScreenRelativePosition(uI.title, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 0.2f);

		// Init Note
		uI.note.setString("note");
		uI.note.setFont(game.font);
		uI.note.setCharacterSize(25);
		uI.note.setFillColor(sf::Color::Yellow);
		SetTextRelativeOrigin(uI.note, 0.5f, 0.5f);
		SetTextScreenRelativePosition(uI.note, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 0.35f);

		// Init Menu Items
		for (int i = 0; i < NUM_MENU_ITEMS; i++)
		{
			uI.menuItems[i].text.setString("item " + std::to_string(i));
			uI.menuItems[i].text.setFont(game.font);
			uI.menuItems[i].text.setCharacterSize(40);
			uI.menuItems[i].text.setFillColor(sf::Color::Yellow);
			SetTextRelativeOrigin(uI.menuItems[i].text, 0.5f, 0.5f);
			SetTextScreenRelativePosition(uI.menuItems[i].text, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 0.5f);
			ShiftTextPozition(uI.menuItems[i].text, 0.f, 50.f * i);
		}

		// Init Score
		uI.score.setString("score");
		uI.score.setFont(game.font);
		uI.score.setCharacterSize(20);
		uI.score.setFillColor(sf::Color::Yellow);
		SetTextRelativeOrigin(uI.score, 0.f, 0.f);
		SetTextScreenRelativePosition(uI.score, SCREEN_WIDTH, SCREEN_HEIGHT, 0.01f, 0.01f);

		//Init tint
		uI.tint.setFillColor(sf::Color(0, 0, 0, 180));
		uI.tint.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	}

	void UpdateHUD(UI& uI, const Game& game)
	{
		UpdateTextAndPosition(uI.score, "Apples Eaten: " + std::to_string(game.numEatenApples));
	}

	void DrawHUD(UI& uI, sf::RenderWindow& window)
	{
		window.draw(uI.score);
	}

	void UpdateMenu(UI& uI, const Game& game)
	{
		for (int i = 0; i < NUM_MENU_ITEMS; i++)
		{
			uI.menuItems[i].text.setFillColor(sf::Color::Yellow);
		}
		uI.menuSelectedItem = uI.menuSelectedItem % NUM_MENU_ITEMS;
		uI.menuItems[uI.menuSelectedItem].text.setFillColor(sf::Color::Red);

		switch (uI.menuState)
		{
		case MenuState::MainMenu:
		{
			UpdateTextAndPosition(uI.note, "Use Arrows to control, eat apples, avoid stones and borders");
			break;
		}
		case MenuState::PauseMenu:
		{
			UpdateTextAndPosition(uI.note, "Current score: " + std::to_string(game.numEatenApples));
			break;
		}
		case MenuState::GameOverMenu:
		{
			UpdateTextAndPosition(uI.note, "Final score: " + std::to_string(game.numEatenApples));
			break;
		}
		}
	}

	void LoadNewMenu(UI& uI)
	{
		for (int i = 0; i < NUM_MENU_ITEMS; i++)
		{
			uI.menuItems[i].isActive = false;
		}
		switch (uI.menuState)
		{
		case MenuState::MainMenu:
		{
			UpdateTextAndPosition(uI.title, "Apples Game!");
			SetMenuItem(uI.menuItems[0], "Start game", MenuEvent::StartGame);
			SetMenuItem(uI.menuItems[1], "Exit game", MenuEvent::ExitGame);
			break;
		}
		case MenuState::PauseMenu:
		{
			UpdateTextAndPosition(uI.title, "Pause");
			SetMenuItem(uI.menuItems[0], "Continue game", MenuEvent::ContinueGame);
			SetMenuItem(uI.menuItems[1], "Restart game", MenuEvent::StartGame);
			SetMenuItem(uI.menuItems[2], "Back to main menu", MenuEvent::BackMainMenu);
			SetMenuItem(uI.menuItems[3], "Exit game", MenuEvent::ExitGame);
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

	void DrawMenu(UI& uI, sf::RenderWindow& window)
	{
		window.draw(uI.tint);
		window.draw(uI.note);
		window.draw(uI.title);
		for (int i = 0; i < NUM_MENU_ITEMS; i++)
		{
			if (uI.menuItems[i].isActive)
			{
				window.draw(uI.menuItems[i].text);
			}
		}
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
		LoadNewMenu(uI);
	}

	MenuEvent GetMenuEvent(UI& uI)
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


