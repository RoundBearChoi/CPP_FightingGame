#pragma once
#include <array>
#include "GameObj.h"
#include "GroupComponent.h"

namespace RB
{
	class FighterDirection : public GroupComponent
	{
	public:
		void Update(std::array<GameObj, 2>& arrObjs) override
		{
			arrObjs[0].objData.UpdateFigherDirection(arrObjs[1].objData);
			arrObjs[1].objData.UpdateFigherDirection(arrObjs[0].objData);
		}
	};
}