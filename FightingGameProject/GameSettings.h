#pragma once
#include <stdint.h>
#include "SceneType.h"
#include "GameData.h"

namespace RB
{
	enum class ChangeTimer
	{
		NONE,
		HALF,
		DOUBLE,
	};

	class GameSettings
	{
	public:
		const static int32_t window_width = 854;
		const static int32_t window_height = 480;
		const static SceneType startingScene = SceneType::FIGHT_SCENE;

		static float TargetFrameTime(ChangeTimer _change)
		{
			static float target = 1.0f / 85.0f;

			if (_change == ChangeTimer::NONE)
			{
				// do nothing
			}
			else if (_change == ChangeTimer::HALF)
			{
				target *= 0.5f;
			}
			else if (_change == ChangeTimer::DOUBLE)
			{
				target *= 2.0f;
			}

			return target;
		}

		static void UpdateTargetFrame(GameData& gameData)
		{
			if (gameData.key_f9)
			{
				gameData.key_f9->processed = true;
				TargetFrameTime(ChangeTimer::DOUBLE);
			}

			if (gameData.key_f10)
			{
				gameData.key_f10->processed = true;
				TargetFrameTime(ChangeTimer::HALF);
			}
		}
	};
}