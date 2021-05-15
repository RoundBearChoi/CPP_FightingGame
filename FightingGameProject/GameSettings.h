#pragma once
#include <stdint.h>
#include "SceneType.h"
#include "GameDataFactory.h"

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
		const static int32_t window_width;
		const static int32_t window_height;
		const static SceneType startingScene;

		static float TargetFrameTime(ChangeTimer _change);
		static void UpdateTargetFrame();
	};
}