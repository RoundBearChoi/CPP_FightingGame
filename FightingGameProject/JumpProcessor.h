#pragma once
#include <stdint.h>

namespace RB
{
	class JumpProcessor
	{
	private:
		size_t updateCount = 0;
		int32_t upForce = 0;
		int32_t horizontalForce = 0;
		const int32_t verticalInterval = 2;
		const int32_t horizontalInterval = 6;

	public:
		bool moveHorizontally = false;
		bool moveBack = false;
		bool allowControl = true;
		int32_t minimumSideForce = 3;

		void SetUpForce(int32_t force)
		{
			upForce = force;
		}

		void SetHorizontalForce(int32_t force)
		{
			horizontalForce = force;
		}

		void UpdateJump(bool upKey, bool forwardKey, bool backKey)
		{
			//vertical
			if (updateCount % verticalInterval == 0 && updateCount != 0)
			{
				//variable up/down speed
				if (allowControl)
				{
					if (upForce > 0)
					{
						if (upKey)
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
				//continuous up/down speed
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
						//variable side speed
						if (allowControl)
						{
							//forward
							if (!moveBack)
							{
								if (forwardKey)
								{
									horizontalForce--;
								}
								else
								{
									horizontalForce -= 2;
								}
							}
							//back
							else
							{
								if (backKey)
								{
									horizontalForce--;
								}
								else
								{
									horizontalForce -= 2;
								}
							}
						}
					}

					if (horizontalForce <= minimumSideForce)
					{
						horizontalForce = minimumSideForce;
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