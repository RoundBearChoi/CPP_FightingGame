#pragma once
#include <iostream>
#include "RenderMode.h"
#include "InputData.h"

namespace RB
{
#define IF_COUT if (DevSettings::use_cout)

	class DevSettings
	{
	public:
		const static bool use_cout = true;
		static RenderMode renderMode;

		static void UpdateDebugBoxSettings();
		static void ChangeRenderMode();
	};
}