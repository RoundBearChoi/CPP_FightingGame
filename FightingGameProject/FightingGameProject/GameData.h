#pragma once
#include "SceneType.h"

namespace RB
{
	class GameData
	{
	public:
		SceneType nextSceneType = SceneType::NONE;

		bool left = false;
		bool right = false;
		bool up = false;
		bool down = false;
	};
}