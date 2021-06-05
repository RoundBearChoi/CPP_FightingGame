#pragma once
#include <stdint.h>

namespace RB
{
	class JumpSpecs
	{
	public:
		JumpSpecs(int32_t upForce, int32_t sideForce, int32_t minimumSideForce, bool moveHorizontally, bool moveBack, bool allowControl)
		{
			mUpForce = upForce;
			mSideForce = sideForce;
			mMinimumSideForce = minimumSideForce;
			mMoveHorizontally = moveHorizontally;
			mMoveBack = moveBack;
			mAllowControl = allowControl;
		}

		int32_t mUpForce = 0;
		int32_t mSideForce = 0;
		int32_t mMinimumSideForce = 0;

		bool mMoveHorizontally = false;
		bool mMoveBack = false;
		bool mAllowControl = false;
	};
}