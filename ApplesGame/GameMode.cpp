#include "GameMode.h"
#include "Constants.h"

namespace ApplesGame
{
	const GameModeNum NumberOfApples{0, 0xFF, MAX_APPLE_COUNT, MIN_APPLE_COUNT};
	const GameModeNum NumberOfStones{8, 0xFF00, MAX_STONE_COUNT, MIN_STONE_COUNT};

	void SetGameModeNum(uint32_t& gameMode, const GameModeNum& gameModeNum, uint8_t newValue)
	{
		uint32_t tempValue = newValue;
		if (newValue > gameModeNum.max_value) tempValue = gameModeNum.max_value;
		if (newValue < gameModeNum.min_value) tempValue = gameModeNum.min_value;

		tempValue <<= static_cast<uint32_t>(gameModeNum.shift);
		gameMode &= ~static_cast<uint32_t>(gameModeNum.mask);
		gameMode |= static_cast<uint32_t>(tempValue);
	}

	void InitGameMode(uint32_t& gameMode)
	{
		SetGameModeFlag(gameMode, GameModeFlag::InfiniteApples);
		SetGameModeFlag(gameMode, GameModeFlag::AcceleratePlayer);
		SetGameModeFlag(gameMode, GameModeFlag::CollideWithBorders);
		SetGameModeFlag(gameMode, GameModeFlag::SpawnSpecialApples);
		SetGameModeNum(gameMode, NumberOfApples, 32);
		SetGameModeNum(gameMode, NumberOfStones, 16);
	}

	void RandomizeGameMode(uint32_t& gameMode)
	{
		gameMode = (rand() & 0xFF) | ((rand() & 0xFF) << 8);
	}

	void SwitchGameModeFlag(uint32_t& gameMode, const GameModeFlag& gameModeFlag)
	{
		gameMode ^= static_cast<uint32_t>(gameModeFlag);
	}

	void SetGameModeFlag(uint32_t& gameMode, const GameModeFlag& gameModeFlag)
	{
		gameMode |= static_cast<uint32_t>(gameModeFlag);
	}

	bool IsGameModeFlagOn(uint32_t gameMode, const GameModeFlag& gameModeFlag)
	{
		return gameMode & static_cast<uint32_t>(gameModeFlag);
	}

	unsigned int GetGameModeNum(uint32_t gameMode, const GameModeNum& gameModeNum)
	{
		return (gameMode & static_cast<uint32_t>(gameModeNum.mask)) >> static_cast<uint32_t>(gameModeNum.shift);
	}

	void AdjustGameModeNum(uint32_t& gameMode, const GameModeNum& gameModeNum, const AdjustmentType& adjustmentType)
	{
		uint8_t numValue = GetGameModeNum(gameMode, gameModeNum);
		switch(adjustmentType)
		{
		case AdjustmentType::Increment:
		{
			if ((numValue) < gameModeNum.max_value)
			{
				numValue++;
				SetGameModeNum(gameMode, gameModeNum, numValue);
			}
			break;
		}
		case AdjustmentType::Decrement:
		{
			if ((numValue) > gameModeNum.min_value)
			{
				numValue--;
				SetGameModeNum(gameMode, gameModeNum, numValue);
			}
			break;
		}
		}
	}

	unsigned int GetNumberOfApples(uint32_t gameMode)
	{
		return GetGameModeNum(gameMode, NumberOfApples);
	}

	void AdjustNumberOfApples(uint32_t& gameMode, const AdjustmentType& adjustmentType)
	{
		AdjustGameModeNum(gameMode, NumberOfApples, adjustmentType);
	}

	unsigned int GetNumberOfStones(uint32_t gameMode)
	{
		return GetGameModeNum(gameMode, NumberOfStones);
	}

	void AdjustNumberOfStones(uint32_t& gameMode, const AdjustmentType& adjustmentType)
	{
		AdjustGameModeNum(gameMode, NumberOfStones, adjustmentType);
	}

	float GetScoreMultiplier(uint32_t gameMode)
	{
		float scoreMultiplier = 1.f;
		if (!IsGameModeFlagOn(gameMode, GameModeFlag::InfiniteApples))
		{
			scoreMultiplier *= 2.f;
		}
		if (!IsGameModeFlagOn(gameMode, GameModeFlag::AcceleratePlayer))
		{
			scoreMultiplier *= 0.5f;
		}
		if (!IsGameModeFlagOn(gameMode, GameModeFlag::CollideWithBorders))
		{
			scoreMultiplier *= 0.8f;
		}
		if (!IsGameModeFlagOn(gameMode, GameModeFlag::SpawnSpecialApples))
		{
			scoreMultiplier *= 1.25f;
		}

		if (GetNumberOfApples(gameMode) > 32)
		{
			scoreMultiplier *= 0.5f + 0.5f * (1.f - (((float)GetNumberOfApples(gameMode) - 32.f)/31.f));
		}
		else
		{
			scoreMultiplier *= 2.f - ((float)GetNumberOfApples(gameMode) / 32.f);
		}

		if (GetNumberOfStones(gameMode) > 16)
		{
			scoreMultiplier *= 1.f + 2.f * (((float)GetNumberOfStones(gameMode) - 16.f) / 47.f);
		}
		else
		{
			scoreMultiplier *= 0.5f + 0.5f * ((float)GetNumberOfStones(gameMode) / 16.f);
		}

		return scoreMultiplier;
	}
}

