#pragma once
#include "SceneType.h"
#include "Key.h"

namespace RB
{
	class GameData
	{
	public:
		SceneType nextSceneType = SceneType::NONE;

		Key* mouse0 = nullptr;

		bool left = false;
		bool right = false;
		bool up = false;
		bool down = false;

		Key* t = nullptr;
		bool a = false;
		bool d = false;
		bool w = false;
		bool s = false;
	};
}