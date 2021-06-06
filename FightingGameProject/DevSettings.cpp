#include "DevSettings.h"

namespace RB
{
	RenderMode DevSettings::renderMode = RenderMode::SPRITES_ONLY;

	void DevSettings::UpdateDebugBoxSettings()
	{
		InputData& inputData = *InputData::ptr;

		if (inputData.key_f8)
		{
			if (!inputData.key_f8->processed)
			{
				inputData.key_f8->processed = true;
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