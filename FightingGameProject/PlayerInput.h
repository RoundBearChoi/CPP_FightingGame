#pragma once

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

		static PlayerInput Get(PlayerType _playerType)
		{
			PlayerInput input;
			InputData& inputData = *InputData::ptr;

			if (_playerType == PlayerType::PLAYER_1)
			{
				if (inputData.key_w) { input.up = true; }
				if (inputData.key_s) { input.down = true; }
				if (inputData.key_a) { input.left = true; }
				if (inputData.key_d) { input.right = true; }

				if (inputData.key_t) { input.weakpunch = true; }
				if (inputData.key_y) { input.strongpunch = true; }
			}
			else if (_playerType == PlayerType::PLAYER_2)
			{
				if (inputData.key_up) { input.up = true; }
				if (inputData.key_down) { input.down = true; }
				if (inputData.key_left) { input.left = true; }
				if (inputData.key_right) { input.right = true; }

				if (inputData.key_np7) { input.weakpunch = true; }
				if (inputData.key_np8) { input.strongpunch = true; }
			}

			return input;
		}
	};
}