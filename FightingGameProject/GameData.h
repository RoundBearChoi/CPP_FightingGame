#pragma once
#include "SceneType.h"
#include "Key.h"

namespace RB
{
	class GameData
	{
	public:
		SceneType nextSceneType = SceneType::NONE;

		//manual camera movement
		Key* key_j = nullptr; //cam left
		Key* key_l = nullptr; //cam right
		Key* key_i = nullptr; //cam zoom
		Key* key_k = nullptr; //cam zoom out

		//player1
		Key* key_t = nullptr; //weak punch
		Key* key_y = nullptr; //strong punch
		Key* key_g = nullptr; //weak kick
		Key* key_h = nullptr; //strong kick

		Key* key_w = nullptr; //up
		Key* key_s = nullptr; //down
		Key* key_a = nullptr; //left
		Key* key_d = nullptr; //right

		//etc
		Key* key_mouse0 = nullptr;
		Key* key_shift = nullptr;
	};
}