#pragma once
#include <iostream>

namespace RB
{
#define DEBUG_MODE

#define IF_COUT if (DevSettings::use_cout)

	class DevSettings
	{
	public:
		const static bool use_cout = true;
	};
}