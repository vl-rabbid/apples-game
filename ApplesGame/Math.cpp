#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <string>

namespace ApplesGame
{
	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * screenWidth;
		result.y = rand() / (float)RAND_MAX * screenHeight;
		return result;
	}

	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
	{
		float dx = (float)fabs(rect1Position.x - rect2Position.x);
		float dy = (float)fabs(rect1Position.y - rect2Position.y);
		return (dx <= (rect1Size.x + rect2Size.x) / 2.f && dy <= (rect1Size.y + rect2Size.y) / 2.f);
	}

	bool IsCirclesCollide(Position2D circ1Position, float circ1Radius, Position2D circ2Position, float circ2Radius)
	{
		float distanceSqr = (circ1Position.x - circ2Position.x) * (circ1Position.x - circ2Position.x)
			+ (circ1Position.y - circ2Position.y) * (circ1Position.y - circ2Position.y);
		return (distanceSqr <= (circ1Radius + circ2Radius) * (circ1Radius + circ2Radius));
	}

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height};
		sprite.setScale(scale);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f origin = { spriteRect.width * originX, spriteRect.height * originY };
		sprite.setOrigin(origin);
	}

	void SetTextRelativeOrigin(sf::Text& text, float originX, float originY)
	{
		sf::FloatRect spriteRect = text.getLocalBounds();
		sf::Vector2f origin = { spriteRect.width * originX, spriteRect.height * originY };
		text.setOrigin(origin);
	}

	Vector2D GetTextRelativeOrigin(sf::Text& text)
	{
		sf::FloatRect spriteRect = text.getLocalBounds();
		sf::Vector2f origin = text.getOrigin();
		Vector2D relativeOrigin;
		relativeOrigin.x = origin.x / spriteRect.width;
		relativeOrigin.y = origin.y / spriteRect.height;
		return relativeOrigin;
	}

	void SetTextScreenRelativePosition(sf::Text& text, float screenWidth, float screenHeight, float relativePositionX, float relativePositionY)
	{
		sf::Vector2f position = { screenWidth * relativePositionX, screenHeight * relativePositionY };
		text.setPosition(position);
	}

	Vector2D GetTextScreenRelativePosition(sf::Text& text, float screenWidth, float screenHeight)
	{
		sf::Vector2f position = text.getPosition();
		Vector2D relativePosition;
		relativePosition.x = position.x / screenWidth;
		relativePosition.y = position.y / screenHeight;
		return relativePosition;
	}

	void ShiftTextPozition(sf::Text& text, float shiftX, float shiftY)
	{
		sf::Vector2f position = text.getPosition();
		position.x += shiftX;
		position.y += shiftY;
		text.setPosition(position);
	}

	bool rollChance(float percent)
	{
		return (rand() / (float)RAND_MAX) < (percent / 100.f);
	}

	std::string BoolToString(const bool& flag)
	{
		if (flag)
		{
			return "Yes";
		}
		return "No";
	}
}
