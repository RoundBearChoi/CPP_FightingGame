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

		Key* left = nullptr;
		Key* right = nullptr;
		Key* up = nullptr;
		Key* down = nullptr;

		Key* t = nullptr;
		Key* a = nullptr;
		Key* d = nullptr;
		Key* w = nullptr;
		Key* s = nullptr;
	};
}