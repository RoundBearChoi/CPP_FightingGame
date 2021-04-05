#include "GameData.h"

namespace RB
{
	Key* GameData::GetWeakPunchKey(PlayerType playerType)
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
}