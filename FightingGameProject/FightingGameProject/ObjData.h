#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class ObjData
	{
	public:
		size_t creationID = 0;
		olc::vf2d position = { 0.0f, 0.0f };
		olc::vf2d spriteSize = { 0.0f, 0.0f };
	};
}