#include "JumpProcessor.h"

namespace RB
{
	JumpProcessor::JumpProcessor()
	{

	}

	void JumpProcessor::SetSpecs(JumpSpecs specs)
	{
		_upForce = specs.mUpForce;
		_horizontalForce = specs.mSideForce;
		_minimumSideForce = specs.mMinimumSideForce;

		_moveHorizontally = specs.mMoveHorizontally;
		_moveBack = specs.mMoveBack;
		_allowControl = specs.mAllowControl;
	}

	int32_t JumpProcessor::GetUpForce() { return _upForce; }
	int32_t JumpProcessor::GetSideForce() { return _horizontalForce; }
	bool JumpProcessor::MoveBack() { return _moveBack; }

	void JumpProcessor::UpdateJump(bool upKey, bool forwardKey, bool backKey)
	{
		//vertical
		if (_updateCount % verticalInterval == 0 && _updateCount != 0)
		{
			//variable up/down speed
			if (_allowControl)
			{
				if (_upForce > 0)
				{
					if (upKey)
					{
						_upForce--;
					}
					else
					{
						_upForce -= 2;
					}
				}
				else
				{
					_upForce--;
				}
			}
			//continuous up/down speed
			else
			{
				_upForce--;
			}
		}

		//horizontal
		if (_moveHorizontally)
		{
			if (_updateCount % horizontalInterval == 0)
			{
				if (_horizontalForce > 3)
				{
					//variable side speed
					if (_allowControl)
					{
						//forward
						if (!_moveBack)
						{
							if (forwardKey)
							{
								_horizontalForce--;
							}
							else
							{
								_horizontalForce -= 2;
							}
						}
						//back
						else
						{
							if (backKey)
							{
								_horizontalForce--;
							}
							else
							{
								_horizontalForce -= 2;
							}
						}
					}
				}

				if (_horizontalForce <= _minimumSideForce)
				{
					_horizontalForce = _minimumSideForce;
				}
			}
		}

		_updateCount++;
	}
}