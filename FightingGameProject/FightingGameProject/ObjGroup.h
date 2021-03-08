#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class ObjGroup
	{
	private:
		size_t creationCount = 0;

	protected:
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
		virtual void RenderObjPosition(olc::PixelGameEngine* ptrEngine, olc::vf2d& camPos) = 0;
	};
}