#pragma once
#include <stdint.h>
#include "SceneType.h"

namespace RB
{
	class GameSettings
	{
	public:
		const static int32_t window_width = 854;
		const static int32_t window_height = 480;
		const static SceneType startingScene = SceneType::BOXCOLLIDER_EDITOR;

		static float TargetFrameTime() { return 1.0f / 20.0f; }
	};
}