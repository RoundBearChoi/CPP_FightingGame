#pragma once
#include <cstdlib>
#include <stdint.h>
#include "JumpSpecs.h"

namespace RB
{
	class JumpCalculator
	{
	private:
		const int32_t verticalInterval = 2;
		const int32_t horizontalInterval = 6;

		size_t _updateCount = 0;
		int32_t _upForce = 0;
		int32_t _horizontalForce = 0;
		int32_t _minimumSideForce = 0;

		bool _moveHorizontally = false;
		bool _moveBack = false;
		bool _allowControl = false;

	public:
		JumpCalculator();

		void SetSpecs(JumpSpecs jumpSpecs);

		int32_t GetUpForce();
		int32_t GetSideForce();
		bool MoveBack();

		void UpdateJump(bool upKey, bool forwardKey, bool backKey);
	};
}