#pragma once
#include <array>
#include "CollidingSideType.h"

namespace RB
{
	class CollisionStay
	{
	public:
		void AddCollidingSide(CollidingSideType sideType)
		{
			_arrIsColliding[(size_t)sideType] = true;
		}

		void ClearAllSides()
		{
			for (size_t i = 0; i < _arrIsColliding.size(); i++)
			{
				_arrIsColliding[i] = false;
			}
		}

		bool IsColliding(CollidingSideType sideType)
		{
			return _arrIsColliding[(size_t)sideType];
		}

	private:
		std::array<bool, 4> _arrIsColliding = { false, false, false, false };
	};
}