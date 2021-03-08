#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class ObjData
	{
	private:
		olc::vf2d position = { 0.0f, 0.0f };
		size_t creationID = 0;

	public:
		olc::vf2d spriteSize = { 0.0f, 0.0f };

		olc::vf2d GetPosition()
		{
			return position;
		}

		void SetPosition(float _x, float _y)
		{
			position.x = _x;
			position.y = _y;
		}

		size_t GetCreationID()
		{
			return creationID;
		}

		void SetCreationID(size_t t)
		{
			creationID = t;
		}
	};
}