#pragma once
#include <iostream>
#include "olcPixelGameEngine.h"

namespace RB
{
	class StringNotification
	{
	public:
		std::string str = "none";
		olc::vi2d pos = { 0, 0 };
		int32_t frames = 0;
		olc::Pixel color = olc::WHITE;

		void Show()
		{
			if (frames > 0)
			{
				frames--;

				olc::Renderer::ptrPGE->DrawString(pos, str, color);
			}
		}
	};
}