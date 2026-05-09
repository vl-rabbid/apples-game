#pragma once
#include <string>
#include <vector>

namespace sf
{
	class Sprite;
	class Text;
}

namespace ApplesGame
{
	enum class AdjustmentType
	{
		Increment = 0,
		Decrement
	};

	struct Vector2D
	{
		float x = 0.f;
		float y = 0.f;
	};

	typedef Vector2D Position2D;

	float GetRandomFloat(float minValue, float maxValue);

	int GetRandomInt(int minValue, int maxValue);

	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight);

	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size);

	bool IsCirclesCollide(Position2D circ1Position, float circ1Radius, Position2D circ2Position, float circ2Radius);

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);

	void SetTextRelativeOrigin(sf::Text& text, float originX, float originY);

	Vector2D GetTextRelativeOrigin(sf::Text& text);

	void SetTextScreenRelativePosition(sf::Text& text, float screenWidth, float screenHeight, float relativePositionX, float relativePositionY);

	Vector2D GetTextScreenRelativePosition(sf::Text& text, float screenWidth, float screenHeight);

	void ShiftTextPozition(sf::Text& text, float shiftX, float shiftY);

	bool rollChance(float percent);

	std::string BoolToString(const bool& flag);

	void SortLeaderboardDesc(std::vector<std::pair<std::string, int>>& leaderboard);
}