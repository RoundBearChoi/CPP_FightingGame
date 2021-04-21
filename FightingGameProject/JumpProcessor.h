#pragma once
#include <cstdlib>
#include <stdint.h>

namespace RB
{
	class JumpProcessor
	{
	private:
		const int32_t verticalInterval = 2;
		const int32_t horizontalInterval = 6;
		size_t updateCount = 0;
		int32_t upForce = 0;
		int32_t horizontalForce = 0;

	public:
		bool moveHorizontally;
		bool moveBack;
		bool allowControl;
		int32_t minimumSideForce;

		JumpProcessor();

		void SetUpForce(int32_t force);
		void SetHorizontalForce(int32_t force);
		int32_t GetUpForce();
		int32_t GetHorizontalForce();

		void UpdateJump(bool upKey, bool forwardKey, bool backKey);
	};
}