#pragma once
#include "SceneType.h"
#include "Key.h"

namespace RB
{
	class GameData
	{
	public:
		SceneType nextSceneType = SceneType::NONE;

		Key* key_mouse0 = nullptr;

		Key* key_left = nullptr;
		Key* key_right = nullptr;
		Key* key_up = nullptr;
		Key* key_down = nullptr;

		Key* key_y = nullptr;
		Key* key_t = nullptr;
		Key* key_g = nullptr;
		Key* key_h = nullptr;
		Key* key_a = nullptr;
		Key* key_d = nullptr;
		Key* key_w = nullptr;
		Key* key_s = nullptr;
	};
}