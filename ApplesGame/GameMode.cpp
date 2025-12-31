#include "GameMode.h"
#include "Constants.h"

namespace ApplesGame
{
	void RandomizeGameMode(GameMode& gameMode)
	{
		gameMode.infiniteApples = rand() % 2;
		gameMode.acceleratePlayer = rand() % 2;
		gameMode.collideWithBorders = rand() % 2;
		gameMode.numberOfApples = rand() % (MAX_NUM_APPLES + 1);
	}

	void InitGameMode(GameMode& gameMode)
	{
		gameMode.infiniteApples = true;
		gameMode.acceleratePlayer = true;
		gameMode.collideWithBorders = true;
		gameMode.numberOfApples = 32;
	}

	bool IsInfiniteApples(const GameMode& gameMode)
	{
		return gameMode.infiniteApples;
	}

	bool IsAcceleratePlayer(const GameMode& gameMode)
	{
		return gameMode.acceleratePlayer;
	}

	bool IsCollideWithBorders(const GameMode& gameMode)
	{
		return gameMode.collideWithBorders;
	}

	int GetNumberOfApples(const GameMode& gameMode)
	{
		return gameMode.numberOfApples;
	}

	void SwitchInfiniteApples(GameMode& gameMode)
	{
		gameMode.infiniteApples = !gameMode.infiniteApples;
	}

	void SwitchAcceleratePlayer(GameMode& gameMode)
	{
		gameMode.acceleratePlayer = !gameMode.acceleratePlayer;
	}

	void SwitchCollideWithBorders(GameMode& gameMode)
	{
		gameMode.collideWithBorders = !gameMode.collideWithBorders;
	}

	void AdjustNumberOfApples(GameMode& gameMode, const AdjustmentType& adjustmentType)
	{
		switch (adjustmentType)
		{
		case AdjustmentType::Increment:
		{
			gameMode.numberOfApples++;
			break;
		}
		case AdjustmentType::Decrement:
		{
			gameMode.numberOfApples--;
			gameMode.numberOfApples += MAX_NUM_APPLES + 1;
			break;
		}
		}
		gameMode.numberOfApples %= MAX_NUM_APPLES + 1;
	}
}

