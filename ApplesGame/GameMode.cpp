#include "GameMode.h"
#include "Constants.h"

namespace ApplesGame
{
	void InitGameMode(uint16_t& gameMode)
	{
		SetGameModeFlag(gameMode, GameModeFlag::InfiniteApples);
		SetGameModeFlag(gameMode, GameModeFlag::AcceleratePlayer);
		SetGameModeFlag(gameMode, GameModeFlag::CollideWithBorders);
		SetGameModeFlag(gameMode, GameModeFlag::SpawnSpecialApples);
		SetGameModeNum(gameMode, GameModeNum::NumApplesMask, GameModeNum::NumApplesShift, 32);
		SetGameModeNum(gameMode, GameModeNum::NumStonesMask, GameModeNum::NumStonesShift, 16);
	}

	void RandomizeGameMode(uint16_t& gameMode)
	{
		gameMode = (rand() & 0xFF) | ((rand() & 0xFF) << 8);
	}

	void SwitchGameModeFlag(uint16_t& gameMode, const GameModeFlag& gameModeFlag)
	{
		gameMode ^= static_cast<uint16_t>(gameModeFlag);
	}

	void SetGameModeFlag(uint16_t& gameMode, const GameModeFlag& gameModeFlag)
	{
		gameMode |= static_cast<uint16_t>(gameModeFlag);
	}

	bool IsGameModeFlagOn(const uint16_t& gameMode, const GameModeFlag& gameModeFlag)
	{
		return gameMode & static_cast<uint16_t>(gameModeFlag);
	}

	std::string IsGameModeFlagOnStr(const uint16_t& gameMode, const GameModeFlag& gameModeFlag)
	{
		return BoolToString(IsGameModeFlagOn(gameMode, gameModeFlag));
	}

	unsigned int GetGameModeNum(const uint16_t& gameMode, const GameModeNum& gameModeMask, const GameModeNum& gameModeShift)
	{
		return (gameMode & static_cast<uint16_t>(gameModeMask)) >> static_cast<uint16_t>(gameModeShift);
	}

	void SetGameModeNum(uint16_t& gameMode, const GameModeNum& gameModeMask, const GameModeNum& gameModeShift, unsigned int newValue)
	{
		newValue <<= static_cast<uint16_t>(gameModeShift);
		newValue &= static_cast<uint16_t>(gameModeMask);
		gameMode &= ~static_cast<uint16_t>(gameModeMask);
		gameMode |= static_cast<uint16_t>(newValue);
	}

	void AdjustGameModeNum(uint16_t& gameMode, const GameModeNum& gameModeMask, const GameModeNum& gameModeShift, const AdjustmentType& adjustmentType)
	{
		unsigned int numValue = GetGameModeNum(gameMode, gameModeMask, gameModeShift);
		switch(adjustmentType)
		{
		case AdjustmentType::Increment:
		{
			numValue++;
			break;
		}
		case AdjustmentType::Decrement:
		{
			numValue--;
			break;
		}
		}
		SetGameModeNum(gameMode, gameModeMask, gameModeShift, numValue);
	}

	unsigned int GetNumberOfApples(const uint16_t& gameMode)
	{
		return GetGameModeNum(gameMode, GameModeNum::NumApplesMask, GameModeNum::NumApplesShift);
	}

	void AdjustNumberOfApples(uint16_t& gameMode, const AdjustmentType& adjustmentType)
	{
		AdjustGameModeNum(gameMode, GameModeNum::NumApplesMask, GameModeNum::NumApplesShift, adjustmentType);
	}

	unsigned int GetNumberOfStones(const uint16_t& gameMode)
	{
		return GetGameModeNum(gameMode, GameModeNum::NumStonesMask, GameModeNum::NumStonesShift);
	}

	void AdjustNumberOfStones(uint16_t& gameMode, const AdjustmentType& adjustmentType)
	{
		AdjustGameModeNum(gameMode, GameModeNum::NumStonesMask, GameModeNum::NumStonesShift, adjustmentType);
	}
}

