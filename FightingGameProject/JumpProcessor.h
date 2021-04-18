#pragma once
#include "GameData.h"
#include "PlayerType.h"
#include "PlayerInput.h"
#include "Directions.h"

namespace RB
{
	class JumpProcessor
	{
	private:
		size_t updateCount = 0;
		int32_t upForce = 0;
		int32_t horizontalForce = 0;
		const int32_t gravityInterval = 4;

	public:
		void SetUpForce(int32_t force)
		{
			upForce = force;
		}

		void SetHorizontalForce(int32_t force)
		{
			horizontalForce = force;
		}

		void UpdateJump(PlayerType playerType, bool isFacingRight, GameData& gameData)
		{
			PlayerInput p = PlayerInput::Get(playerType, gameData);

			if (updateCount % gravityInterval == 0 && updateCount != 0)
			{
				if (upForce > 0)
				{
					if (p.up)
					{
						upForce--;
					}
					else
					{
						upForce -= 2;
					}
				}
				else
				{
					upForce--;
				}

				if (horizontalForce > 1)
				{
					Directions d = Directions::Get(isFacingRight, p);

					if (d.forward)
					{

					}
					else
					{
						int n = 0;
					}
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