#pragma once
#include <string>

namespace ApplesGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const float INITIAL_SPEED = 100.f; // Pixel per second
	const float ACCELERATION = 20.f; // Acceleration per apple eaten
	const float PLAYER_SIZE = 20.f;
	const int MAX_NUM_APPLES = 64;
	const float APPLE_SIZE = 20.f;
	const float SPECIAL_APPLE_CHANCE = 10;
	const int POINTS_FOR_APPLE = 10;
	const int MAX_NUM_STONES = 64;
	const float STONE_SIZE = 15.f;
	const int NUM_MENU_ITEMS = 7;
}