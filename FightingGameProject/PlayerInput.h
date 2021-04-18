#pragma once
#include "GameData.h"

namespace RB
{
	class PlayerInput
	{
	public:
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
		
		bool weakpunch = false;
		bool strongpunch = false;

		bool weakkick = false;
		bool strongkick = false;

		static PlayerInput Get(PlayerType _playerType, GameData& gameData)
		{
			PlayerInput input;

			if (_playerType == PlayerType::PLAYER_1)
			{
				if (gameData.key_w) { input.up = true; }
				if (gameData.key_s) { input.down = true; }
				if (gameData.key_a) { input.left = true; }
				if (gameData.key_d) { input.right = true; }

				if (gameData.key_t) { input.weakpunch = true; }
			}
			else if (_playerType == PlayerType::PLAYER_2)
			{
				if (gameData.key_up) { input.up = true; }
				if (gameData.key_down) { input.down = true; }
				if (gameData.key_left) { input.left = true; }
				if (gameData.key_right) { input.right = true; }

				if (gameData.key_np7) { input.weakpunch = true; }
			}

			return input;
		}
	};
}