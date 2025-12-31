#pragma once
#include "Math.h"

namespace ApplesGame
{
	struct GameMode
	{
		bool infiniteApples;
		bool acceleratePlayer;
		bool collideWithBorders;
		int numberOfApples;
	};

	void RandomizeGameMode(GameMode& gameMode);

	void InitGameMode(GameMode& gameMode);

	bool IsInfiniteApples(const GameMode& gameMode);

	bool IsAcceleratePlayer(const GameMode& gameMode);

	bool IsCollideWithBorders(const GameMode& gameMode);

	int GetNumberOfApples(const GameMode& gameMode);

	void SwitchInfiniteApples(GameMode& gameMode);

	void SwitchAcceleratePlayer(GameMode& gameMode);

	void SwitchCollideWithBorders(GameMode& gameMode);

	void AdjustNumberOfApples(GameMode& gameMode, const AdjustmentType& adjustmentType);
}