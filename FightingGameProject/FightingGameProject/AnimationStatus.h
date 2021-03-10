#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class AnimationStatus
	{
	public:
		int decalTypeIndex = 0;

		int32_t nCurrentTile = 0;
		int32_t nTransitionDelay = 0;
		int32_t nDelayCount = 0;

		bool bPlayOnce = false;
		bool bReverseDecal = false;

		olc::vi2d sourcePos = { 0, 0 };
		olc::vi2d sourceSize = { 0, 0 };
	};
}