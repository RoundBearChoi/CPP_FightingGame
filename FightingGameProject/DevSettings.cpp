#include "DevSettings.h"

namespace RB
{
	RenderMode DevSettings::renderMode = RenderMode::SPRITES_ONLY;

	void DevSettings::UpdateDebugBoxSettings()
	{
		GameData& gameData = *GameDataFactory::ptr->GetGameData();

		if (gameData.key_f8)
		{
			if (!gameData.key_f8->processed)
			{
				gameData.key_f8->processed = true;
				ChangeRenderMode();
			}

		}
	}

	void DevSettings::ChangeRenderMode()
	{
		int32_t mode = (int32_t)renderMode;

		mode++;

		if (mode < 0)
		{
			mode = (int32_t)RenderMode::COUNT - 1;
		}

		if (mode >= (int32_t)RenderMode::COUNT)
		{
			mode = 0;
		}

		renderMode = (RenderMode)mode;

		IF_COUT{ std::cout << "render mode: " << (int32_t)renderMode << std::endl; }
	}
}