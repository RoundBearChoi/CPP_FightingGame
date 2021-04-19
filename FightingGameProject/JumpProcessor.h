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
		const int32_t horizontalInterval = 8;

	public:
		bool moveHorizontally = false;
		bool moveBack = false;

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

			//vertical
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
			}

			//horizontal
			if (moveHorizontally)
			{
				if (updateCount % horizontalInterval == 0)
				{
					if (horizontalForce > 3)
					{
						Directions d = Directions::Get(isFacingRight, p);

						if (!moveBack)
						{
							if (d.forward)
							{
								horizontalForce--;
							}
							else
							{
								horizontalForce -= 2;
							}
						}
						else
						{
							if (d.back)
							{
								horizontalForce--;
							}
							else
							{
								horizontalForce -= 2;
							}
						}
					}

					if (horizontalForce <= 3)
					{
						horizontalForce = 3;
					}
				}
			}

			updateCount++;
		}

		int32_t GetUpForce()
		{
			return upForce;
		}

		int32_t GetHorizontalForce()
		{
			return horizontalForce;
		}
	};
}