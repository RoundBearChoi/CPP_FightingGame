#pragma once
#include "GameData.h"
#include "PlayerType.h"
#include "PlayerInput.h"

namespace RB
{
	class JumpProcessor
	{
	private:
		size_t updateCount = 0;
		int32_t upForce = 0;
		const int32_t gravityInterval = 4;

	public:
		void SetUpForce(int32_t force)
		{
			upForce = force;
		}

		void UpdateJump(PlayerType playerType, GameData& gameData)
		{


			PlayerInput p = PlayerInput::Get(playerType, gameData);

			if (updateCount % gravityInterval == 0 && updateCount != 0)
			{
				upForce--;

				if (p.up)
				{
					int n = 0;
				}
				else
				{
					int n = 0;
				}
			}

			updateCount++;
		}

		int32_t GetUpForce()
		{
			return upForce;
		}
	};
}