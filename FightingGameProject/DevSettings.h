#pragma once
#include <iostream>
#include "GameData.h"

namespace RB
{
#define IF_COUT if (DevSettings::use_cout)

	class DevSettings
	{
	public:
		const static bool use_cout = true;
		static bool renderDebugBoxes;

		static void UpdateDebugBoxSettings(GameData& gameData)
		{
			if (gameData.key_f8)
			{
				if (renderDebugBoxes)
				{
					gameData.key_f8->processed = true;
					renderDebugBoxes = false;
				}
				else
				{
					gameData.key_f8->processed = true;
					renderDebugBoxes = true;
				}
			}
		}
	};
}