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
		const static SceneType startingScene = SceneType::HITBOX_EDITOR_SCENE;

		static float TargetFrameTime() { return 1.0f / 120.0f; }
	};
}