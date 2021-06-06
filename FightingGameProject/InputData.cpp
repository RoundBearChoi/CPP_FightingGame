#include "InputData.h"

namespace RB
{
	InputData* InputData::ptr = nullptr;

	Key* InputData::GetWeakPunchKey(PlayerType playerType)
	{
		if (playerType == PlayerType::PLAYER_1)
		{
			return key_t;
		}
		else if (playerType == PlayerType::PLAYER_2)
		{
			return key_np7;
		}

		return nullptr;
	}

	void InputData::ResetInputData()
	{
		if (ptr != nullptr)
		{
			delete ptr;
		}

		ptr = new InputData();
	}
}