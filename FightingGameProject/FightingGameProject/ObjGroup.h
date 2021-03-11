#pragma once
#include "olcPixelGameEngine.h"
#include "Camera.h"

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
		virtual void RenderObjPosition(olc::PixelGameEngine* ptrEngine, Camera& cam) = 0;
		virtual void RenderStates(olc::PixelGameEngine* ptrEngine, DecalLoader* ptrDecalLoader, Camera& cam, bool update) = 0;
	};
}
