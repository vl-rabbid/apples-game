#pragma once
#include "Math.h"

namespace ApplesGame
{
	struct GameModeNum
	{
		uint32_t shift;
		uint32_t mask;
		uint8_t max_value;
		uint8_t min_value;
	};

	extern const GameModeNum NumberOfApples;
	extern const GameModeNum NumberOfStones;

	enum class GameModeFlag : uint32_t
	{
		InfiniteApples = (1 << 31),
		AcceleratePlayer = (1 << 30),
		CollideWithBorders = (1 << 29),
		SpawnSpecialApples = (1 << 28)
	};

	void InitGameMode(uint32_t& gameMode);

	void RandomizeGameMode(uint32_t& gameMode);

	void SwitchGameModeFlag(uint32_t& gameMode, const GameModeFlag& gameModeFlag);

	void SetGameModeFlag(uint32_t& gameMode, const GameModeFlag& gameModeFlag);

	bool IsGameModeFlagOn(uint32_t gameMode, const GameModeFlag& gameModeFlag);

	unsigned int GetNumberOfApples(uint32_t gameMode);

	void AdjustNumberOfApples(uint32_t& gameMode, const AdjustmentType& adjustmentType);

	unsigned int GetNumberOfStones(uint32_t gameMode);

	void AdjustNumberOfStones(uint32_t& gameMode, const AdjustmentType& adjustmentType);

	float GetScoreMultiplier(uint32_t gameMode);
}