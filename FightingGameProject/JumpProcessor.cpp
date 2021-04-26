#include "JumpProcessor.h"

namespace RB
{
	JumpProcessor::JumpProcessor()
	{
		moveHorizontally = false;
		moveBack = false;
		allowControl = true;
		minimumSideForce = 3;
	}

	void JumpProcessor::SetUpForce(int32_t force) { upForce = force; }
	void JumpProcessor::SetSideForce(int32_t force) { horizontalForce = force; }
	int32_t JumpProcessor::GetUpForce() { return upForce; }
	int32_t JumpProcessor::GetSideForce() { return horizontalForce; }

	void JumpProcessor::UpdateJump(bool upKey, bool forwardKey, bool backKey)
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
}