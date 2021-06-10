#pragma once
#include <array>
#include "CollidingSideType.h"

namespace RB
{
	class FighterCollisionStay
	{
	private:
		ObjData* _objData = nullptr;
		std::array<bool, 4> _arrIsColliding = { false, false, false, false };

	public:
		FighterCollisionStay(ObjData* objData)
		{
			_objData = objData;
		}

		void AddCollidingSide(CollidingSideType sideType)
		{
			_arrIsColliding[(size_t)sideType] = true;
		}

		void AddCollidingSide(olc::vi2d midPoint)
		{
			if (midPoint.x < _objData->GetPosition().x)
			{
				AddCollidingSide(CollidingSideType::LEFT);
			}
			else if (midPoint.x > _objData->GetPosition().x)
			{
				AddCollidingSide(CollidingSideType::RIGHT);
			}
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
	};
}