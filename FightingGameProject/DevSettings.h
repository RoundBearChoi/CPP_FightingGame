#pragma once
#include <iostream>
#include "RenderMode.h"
#include "GameDataFactory.h"

namespace RB
{
#define IF_COUT if (DevSettings::use_cout)

	class DevSettings
	{
	public:
		const static bool use_cout = true;
		static RenderMode renderMode;
		static GameDataFactory* gameDataFactory;

		static void UpdateDebugBoxSettings();
		static void ChangeRenderMode();
	};
}