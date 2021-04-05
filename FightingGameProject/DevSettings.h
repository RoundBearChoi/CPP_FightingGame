#pragma once
#include <iostream>
#include "GameData.h"
#include "RenderMode.h"

namespace RB
{
#define IF_COUT if (DevSettings::use_cout)

	class DevSettings
	{
	public:
		const static bool use_cout = true;
		static bool renderDebugBoxes;
		static RenderMode renderMode;

		static void UpdateDebugBoxSettings(GameData& gameData)
		{
			if (gameData.key_f8)
			{
				if (!gameData.key_f8->processed)
				{
					gameData.key_f8->processed = true;

					if (renderDebugBoxes)
					{
						renderDebugBoxes = false;
					}
					else
					{
						renderDebugBoxes = true;
					}

					ChangeRenderMode();
				}

			}
		}

		static void ChangeRenderMode()
		{
			int32_t mode = (int32_t)renderMode;

			mode++;

			if (mode < (int32_t)RenderMode::NONE)
			{
				mode = (int32_t)RenderMode::COUNT - 1;
			}

			if (mode >= (int32_t)RenderMode::COUNT)
			{
				mode = (int32_t)RenderMode::NONE;
			}

			renderMode = (RenderMode)mode;

			IF_COUT{ std::cout << "render mode: " << (int32_t)renderMode << std::endl; }
		}
	};
}