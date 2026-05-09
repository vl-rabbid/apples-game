#include "UI.h"
#include "Game.h"
#include "Math.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	void InitUI(UI& uI, const Game& game)
	{
		// Init Menu Title
		uI.title.setString("title");
		uI.title.setFont(game.font);
		uI.title.setStyle(sf::Text::Bold);
		uI.title.setCharacterSize(100);
		uI.title.setFillColor(sf::Color::Yellow);
		SetTextRelativeOrigin(uI.title, 0.5f, 0.5f);
		SetTextScreenRelativePosition(uI.title, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 0.1f);

		// Init Note
		uI.note.setString("note");
		uI.note.setFont(game.font);
		uI.note.setCharacterSize(30);
		uI.note.setFillColor(sf::Color::Yellow);
		SetTextRelativeOrigin(uI.note, 0.5f, 0.5f);
		SetTextScreenRelativePosition(uI.note, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 0.25f);

		// Init Menu Items
		for (int i = 0; i < NUM_MENU_ITEMS; i++)
		{
			uI.menuItems[i].text.setString("item " + std::to_string(i));
			uI.menuItems[i].text.setFont(game.font);
			uI.menuItems[i].text.setCharacterSize(32);
			uI.menuItems[i].text.setFillColor(sf::Color::Yellow);
			SetTextRelativeOrigin(uI.menuItems[i].text, 0.5f, 0.5f);
		}

		// Init Player Score
		uI.playerScore.setString("score");
		uI.playerScore.setFont(game.font);
		uI.playerScore.setCharacterSize(20);
		uI.playerScore.setFillColor(sf::Color::Yellow);
		SetTextRelativeOrigin(uI.playerScore, 0.f, 0.f);
		SetTextScreenRelativePosition(uI.playerScore, SCREEN_WIDTH, SCREEN_HEIGHT, 0.01f, 0.01f);

		//Init tint
		uI.tint.setFillColor(sf::Color(0, 0, 0, 180));
		uI.tint.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

		//Init Leaderboard
		uI.showLeaderboard = false;
		for (int i = 0; i < LEADERBOARD_DISPLAY_SIZE; i++)
		{
			uI.leaderboardItems[i].setString("score " + std::to_string(i));
			uI.leaderboardItems[i].setFont(game.font);
			uI.leaderboardItems[i].setCharacterSize(32);
			uI.leaderboardItems[i].setFillColor(sf::Color::Yellow);
			SetTextRelativeOrigin(uI.leaderboardItems[i], 0.5f, 0.5f);
			SetTextScreenRelativePosition(uI.leaderboardItems[i], SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 0.4f);
			ShiftTextPozition(uI.leaderboardItems[i], 0.f, 42.f * i);
		}
		LoadLeaderboard(uI, game);

		// Init New Record text
		uI.newRecord.setString("New personal record!!!");
		uI.newRecord.setFont(game.font);
		uI.newRecord.setCharacterSize(35);
		uI.newRecord.setFillColor(sf::Color::Yellow);
		SetTextRelativeOrigin(uI.newRecord, 0.5f, 0.5f);
		SetTextScreenRelativePosition(uI.newRecord, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 0.30f);
	}

	void UpdateHUD(UI& uI, const Game& game)
	{
		UpdateTextAndPosition(uI.playerScore, "Score: " + std::to_string(game.playerScore));
	}

	void DrawHUD(UI& uI, sf::RenderWindow& window)
	{
		window.draw(uI.playerScore);
	}

	void UpdateMenu(UI& uI, const Game& game, const float deltaTime)
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
		case MenuState::GameModeMenu:
		{
			UpdateTextAndPosition(uI.note,"Try every combination!!!");

			UpdateItemString(uI.menuItems[1], ("< Infinite Apples : " + BoolToString(IsGameModeFlagOn(game.gameMode, GameModeFlag::InfiniteApples)) + " >"));
			UpdateItemString(uI.menuItems[2], ("< Accelerate Player : " + BoolToString(IsGameModeFlagOn(game.gameMode, GameModeFlag::AcceleratePlayer)) + " >"));
			UpdateItemString(uI.menuItems[3], ("< Collide with Borders : " + BoolToString(IsGameModeFlagOn(game.gameMode, GameModeFlag::CollideWithBorders)) + " >"));
			UpdateItemString(uI.menuItems[4], ("< Spawn special Apples : " + BoolToString(IsGameModeFlagOn(game.gameMode, GameModeFlag::SpawnSpecialApples)) + " >"));
			UpdateItemString(uI.menuItems[5], ("< Number of Apples : " + std::to_string(GetNumberOfApples(game.gameMode)) + " >"));
			UpdateItemString(uI.menuItems[6], ("< Number of Stones : " + std::to_string(GetNumberOfStones(game.gameMode)) + " >"));
			break;
		}
		case MenuState::PauseMenu:
		{
			UpdateTextAndPosition(uI.note, "Current score: " + std::to_string(game.playerScore));
			break;
		}
		case MenuState::GameOverMenu:
		{
			if (uI.showNewRecordText)
			{
				UpdateBlinkText(uI.newRecord, 0.3f, deltaTime);
			}
			UpdateTextAndPosition(uI.note, "Final score: " + std::to_string(game.playerScore));
			break;
		}
		case MenuState::LeaderboardMenu:
		{
			UpdateTextAndPosition(uI.note, "Set a new record!!!");
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
		uI.showLeaderboard = false;
		switch (uI.menuState)
		{
		case MenuState::MainMenu:
		{
			UpdateTextAndPosition(uI.title, "Apples Game!");
			SetMenuItemsPosition(uI, .0f, .0f);
			SetMenuItem(uI.menuItems[0], "Start game", MenuItemType::StartGame);
			SetMenuItem(uI.menuItems[1], "Game mode", MenuItemType::GameMode);
			SetMenuItem(uI.menuItems[2], "Leaderboard", MenuItemType::Leaderboard);
			SetMenuItem(uI.menuItems[3], "Exit game", MenuItemType::ExitGame);
			break;
		}
		case MenuState::GameModeMenu:
		{
			UpdateTextAndPosition(uI.title, "Game mode");
			SetMenuItemsPosition(uI, .0f, .0f);
			SetMenuItem(uI.menuItems[0], "Randomize", MenuItemType::RandomizeGameMode);
			SetMenuItem(uI.menuItems[1], "Infinite Apples", MenuItemType::InfiniteApples);
			SetMenuItem(uI.menuItems[2], "Accelerate Player", MenuItemType::AcceleratePlayer);
			SetMenuItem(uI.menuItems[3], "Collide with Borders", MenuItemType::CollideWithBorders);
			SetMenuItem(uI.menuItems[4], "Spawn special Apples", MenuItemType::SpawnSpecialApples);
			SetMenuItem(uI.menuItems[5], "Number of Apples", MenuItemType::NumberOfApples);
			SetMenuItem(uI.menuItems[6], "Number of Stones", MenuItemType::NumberOfStones);
			SetMenuItem(uI.menuItems[7], "Back", MenuItemType::BackMainMenu);
			break;
		}
		case MenuState::PauseMenu:
		{
			UpdateTextAndPosition(uI.title, "Pause");
			SetMenuItemsPosition(uI, .0f, .0f);
			SetMenuItem(uI.menuItems[0], "Continue game", MenuItemType::ContinueGame);
			SetMenuItem(uI.menuItems[1], "Restart game", MenuItemType::StartGame);
			SetMenuItem(uI.menuItems[2], "Back to main menu", MenuItemType::BackMainMenu);
			SetMenuItem(uI.menuItems[3], "Exit game", MenuItemType::ExitGame);
			break;
		}
		case MenuState::GameOverMenu:
		{
			uI.showLeaderboard = true;
			SetMenuItemsPosition(uI, .0f, 300.0f);
			UpdateTextAndPosition(uI.title, "GAME OVER");
			SetMenuItem(uI.menuItems[0], "Restart game", MenuItemType::StartGame);
			SetMenuItem(uI.menuItems[1], "Back to main menu", MenuItemType::BackMainMenu);
			SetMenuItem(uI.menuItems[2], "Exit game", MenuItemType::ExitGame);
			break;
		}
		case MenuState::LeaderboardMenu:
		{
			uI.showLeaderboard = true;
			SetMenuItemsPosition(uI, .0f, 300.0f);
			UpdateTextAndPosition(uI.title, "Leaderboard");
			SetMenuItem(uI.menuItems[0], "Back", MenuItemType::BackMainMenu);
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
		if (uI.showLeaderboard)
		{
			for (int i = 0; i < LEADERBOARD_DISPLAY_SIZE; i++)
			{
				window.draw(uI.leaderboardItems[i]);
			}
		}
		if (uI.showNewRecordText)
		{
			window.draw(uI.newRecord);
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
		uI.showNewRecordText = false;
		uI.menuState = menuState;
		uI.menuSelectedItem = 0;
		LoadNewMenu(uI);
	}

	MenuItemType GetMenuItemType(UI& uI)
	{
		uI.menuSelectedItem = uI.menuSelectedItem % NUM_MENU_ITEMS;
		return uI.menuItems[uI.menuSelectedItem].itemType;
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

	void SetMenuItemsPosition(UI& uI, float shiftX, float shiftY)
	{
		for (int i = 0; i < NUM_MENU_ITEMS; i++)
		{
			SetTextScreenRelativePosition(uI.menuItems[i].text, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 0.4f);
			ShiftTextPozition(uI.menuItems[i].text, shiftX + 0.f , shiftY + (42.f * i));
		}
	}

	void LoadLeaderboard(UI& uI, const Game& game)
	{
		int displayCount = LEADERBOARD_DISPLAY_SIZE;
		if (game.leaderboard.size() < LEADERBOARD_DISPLAY_SIZE)
		{
			displayCount = game.leaderboard.size();
		}

		for (int i = 0; i < displayCount; i++)
		{
			Vector2D relativePosition = GetTextScreenRelativePosition(uI.leaderboardItems[i], SCREEN_WIDTH, SCREEN_HEIGHT);
			Vector2D relativeOrigin = GetTextRelativeOrigin(uI.leaderboardItems[i]);

			std::string textString = game.leaderboard[i].name + ".";
			do
			{
				uI.leaderboardItems[i].setString(textString + std::to_string(game.leaderboard[i].score));
				textString = textString + ".";

			} while (uI.leaderboardItems[i].getLocalBounds().width < LEADERBOARD_WIDTH);

			SetTextRelativeOrigin(uI.leaderboardItems[i], relativeOrigin.x, relativeOrigin.y);
			SetTextScreenRelativePosition(uI.leaderboardItems[i], SCREEN_WIDTH, SCREEN_HEIGHT, relativePosition.x, relativePosition.y);
		}
	}

	void UpdateBlinkText(sf::Text& text, const float blinkInterval, const float deltaTime) {
		static float blinkAccumulator = 0.f;
		static bool isRed = true;

		blinkAccumulator += deltaTime;
		if (blinkAccumulator >= blinkInterval) {
			blinkAccumulator -= blinkInterval;
			if (isRed) {
				text.setFillColor(sf::Color::Yellow);
			}
			else {
				text.setFillColor(sf::Color::Red);
			}
			isRed = !isRed;
		}
	}
}


