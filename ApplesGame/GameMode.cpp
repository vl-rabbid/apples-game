#include "GameMode.h"
#include "Constants.h"

namespace ApplesGame
{
	void RandomizeGameMode(GameMode& gameMode)
	{
		gameMode.infiniteApples = rand() % 2;
		gameMode.acceleratePlayer = rand() % 2;
		gameMode.collideWithBorders = rand() % 2;
		gameMode.numberOfApples = rand() % (MAX_NUM_APPLES);
		gameMode.numberOfStones = rand() % (MAX_NUM_STONES);
	}

	void InitGameMode(GameMode& gameMode)
	{
		gameMode.infiniteApples = true;
		gameMode.acceleratePlayer = true;
		gameMode.collideWithBorders = true;
		gameMode.numberOfApples = 32;
		gameMode.numberOfStones = 16;
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

	int GetNumberOfStones(const GameMode& gameMode)
	{
		return gameMode.numberOfStones;
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
			gameMode.numberOfApples += MAX_NUM_APPLES;
			break;
		}
		}
		gameMode.numberOfApples %= MAX_NUM_APPLES;
	}

	void AdjustNumberOfStones(GameMode& gameMode, const AdjustmentType& adjustmentType)
	{
		switch (adjustmentType)
		{
		case AdjustmentType::Increment:
		{
			gameMode.numberOfStones++;
			break;
		}
		case AdjustmentType::Decrement:
		{
			gameMode.numberOfStones--;
			gameMode.numberOfStones += MAX_NUM_STONES;
			break;
		}
		}
		gameMode.numberOfStones %= MAX_NUM_STONES;
	}
}

