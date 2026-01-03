#pragma once
#include "Math.h"
#include <string>

namespace ApplesGame
{
	enum class GameModeFlag : uint16_t
	{
		InfiniteApples = (1 << 15),
		AcceleratePlayer = (1 << 14),
		CollideWithBorders = (1 << 13),
		SpawnSpecialApples = (1 << 12)
	};

	enum class GameModeNum : uint16_t
	{
		NumApplesMask = 0x003F,
		NumApplesShift = 0,
		NumStonesMask = 0x0FC0,
		NumStonesShift = 6
	};

	void InitGameMode(uint16_t& gameMode);

	void RandomizeGameMode(uint16_t& gameMode);

	void SwitchGameModeFlag(uint16_t& gameMode, const GameModeFlag& gameModeFlag);

	void SetGameModeFlag(uint16_t& gameMode, const GameModeFlag& gameModeFlag);

	bool IsGameModeFlagOn(const uint16_t& gameMode, const GameModeFlag& gameModeFlag);

	std::string IsGameModeFlagOnStr(const uint16_t& gameMode, const GameModeFlag& gameModeFlag);

	unsigned int GetGameModeNum(const uint16_t& gameMode, const GameModeNum& gameModeMask, const GameModeNum& gameModeShift);

	void SetGameModeNum(uint16_t& gameMode, const GameModeNum& gameModeMask, const GameModeNum& gameModeShift, unsigned int newValue);

	void AdjustGameModeNum(uint16_t& gameMode, const GameModeNum& gameModeMask, const GameModeNum& gameModeShift, const AdjustmentType& adjustmentType);

	unsigned int GetNumberOfApples(const uint16_t& gameMode);

	void AdjustNumberOfApples(uint16_t& gameMode, const AdjustmentType& adjustmentType);

	unsigned int GetNumberOfStones(const uint16_t& gameMode);

	void AdjustNumberOfStones(uint16_t& gameMode, const AdjustmentType& adjustmentType);
}