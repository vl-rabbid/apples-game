#pragma once
#include "Math.h"
#include <vector>

namespace ApplesGame
{
	struct GameModeNum
	{
		uint32_t shift;
		uint32_t mask;
		uint8_t max_value;
		uint8_t min_value;
	};

	struct Record
	{
		std::string name;
		int score;
	};

	extern const GameModeNum NumberOfApples;
	extern const GameModeNum NumberOfStones;

	enum class GameModeFlag : uint32_t
	{
		InfiniteApples = (1 << 17),
		AcceleratePlayer = (1 << 18),
		CollideWithBorders = (1 << 19),
		SpawnSpecialApples = (1 << 20)
	};

	void InitGameMode(uint32_t& gameMode);

	void RandomizeGameMode(uint32_t& gameMode);

	void SwitchGameModeFlag(uint32_t& gameMode, const GameModeFlag& gameModeFlag);

	void SetGameModeFlag(uint32_t& gameMode, const GameModeFlag& gameModeFlag, bool newValue);

	bool IsGameModeFlagOn(uint32_t gameMode, const GameModeFlag& gameModeFlag);

	uint32_t GetNumberOfApples(uint32_t gameMode);

	void AdjustNumberOfApples(uint32_t& gameMode, const AdjustmentType& adjustmentType);

	uint32_t GetNumberOfStones(uint32_t gameMode);

	void AdjustNumberOfStones(uint32_t& gameMode, const AdjustmentType& adjustmentType);

	float GetScoreMultiplier(uint32_t gameMode);

	bool isGameModeConsistent(uint32_t gameMode);

	void SortLeaderboard(std::vector<Record>& leaderboard);
}