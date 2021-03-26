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

		//player2
		Key* key_np7 = nullptr; //weak punch
		Key* key_np8 = nullptr; //strong punch
		Key* key_np4 = nullptr; //weak kick
		Key* key_np5 = nullptr; //strong kick

		Key* key_up = nullptr; //up
		Key* key_down = nullptr; //down
		Key* key_left = nullptr; //left
		Key* key_right = nullptr; //right

		//etc
		Key* key_mouse0 = nullptr;
		Key* key_shift = nullptr;
		Key* key_f8 = nullptr;
		Key* key_f9 = nullptr;
		Key* key_f10 = nullptr;
		Key* key_f11 = nullptr;
	};
}