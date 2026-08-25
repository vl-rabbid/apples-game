#pragma once
#include <string>
#include <cstdint>

namespace ApplesGame
{
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 750;
	const float INITIAL_SPEED = 100.f; // Pixel per second
	const float ACCELERATION = 20.f; // Acceleration per apple eaten
	const float PLAYER_SIZE = 20.f;
	const float APPLE_SIZE = 20.f;
	const uint8_t MAX_APPLE_COUNT = 60;
	const uint8_t MIN_APPLE_COUNT = 4;
	const uint8_t MAX_STONE_COUNT = 32;
	const uint8_t MIN_STONE_COUNT = 0;
	const float SPECIAL_APPLE_CHANCE = 10;
	const int POINTS_FOR_APPLE = 100;
	const float STONE_SIZE = 15.f;
	const int NUM_MENU_ITEMS = 8;
	const int LEADERBOARD_DISPLAY_SIZE = 5;
	const float LEADERBOARD_WIDTH = 500.f;
	const std::string PLAYER_NAME = "Player";
}
