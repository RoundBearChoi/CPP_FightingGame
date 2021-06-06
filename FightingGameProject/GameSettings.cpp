#include "GameSettings.h"

namespace RB
{
	const int32_t GameSettings::window_width = 854;
	const int32_t GameSettings::window_height = 480;
	const SceneType GameSettings::startingScene = SceneType::FIGHT_SCENE;

	float GameSettings::TargetFrameTime(ChangeTimer _change)
	{
		static float target = 1.0f / 80.0f;

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

	void GameSettings::UpdateTargetFrame()
	{
		InputData& inputData = *InputData::ptr;

		if (inputData.key_f9)
		{
			inputData.key_f9->processed = true;
			TargetFrameTime(ChangeTimer::DOUBLE);
		}

		if (inputData.key_f10)
		{
			inputData.key_f10->processed = true;
			TargetFrameTime(ChangeTimer::HALF);
		}
	}
}