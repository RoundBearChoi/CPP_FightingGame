#pragma once
#include <iostream>

namespace RB
{
#define IF_COUT if (DevSettings::use_cout)

	class DevSettings
	{
	public:
		const static bool use_cout = true;

		static bool RenderDebugBoxes(bool _render)
		{
			static bool render = false;

			render = _render;

			return render;
		}
	};
}