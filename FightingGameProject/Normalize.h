#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class Normalize
	{
	public:
		static olc::vf2d Norm(olc::vi2d vec)
		{
			olc::vf2d norm = (olc::vf2d)vec * 1.0f / (float)vec.mag();
			return norm;
		}
	};
}