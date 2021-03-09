#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class ObjGroup
	{
	protected:
		size_t creationCount = 0;

		size_t GetCreationCount()
		{
			creationCount++;

			if (creationCount > (size_t)-1)
			{
				creationCount = 0;
			}

			return creationCount;
		}

	public:
		virtual void RenderObjPosition(olc::PixelGameEngine* ptrEngine, const olc::vi2d& camPos, const float& zoomScale) = 0;
	};
}
