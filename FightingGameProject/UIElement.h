#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class UIElement
	{
	public:
		olc::vi2d topLeft;
		int32_t width;
		int32_t height;
		olc::Decal* ptrDecal;

		bool MouseHovering(olc::vi2d& mousePos)
		{
			if (mousePos.x >= topLeft.x && mousePos.x <= topLeft.x + width)
			{
				if (mousePos.y >= topLeft.y && mousePos.y <= topLeft.y + height)
				{
					return true;
				}
			}

			return false;
		}
	};
}