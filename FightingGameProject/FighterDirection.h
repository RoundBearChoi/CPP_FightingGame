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
			UpdateFigherDirection(arrObjs[0].objData, arrObjs[1].objData);
			UpdateFigherDirection(arrObjs[1].objData, arrObjs[0].objData);
		}

		void UpdateFigherDirection(ObjData& me, ObjData& enemy)
		{
			//only turn when grounded
			if (me.GetPosition().y == 0)
			{
				if (me.GetPosition().x < enemy.GetPosition().x)
				{
					me.SetLeftSide(true);
					me.FaceRight(true);
				}
				else if (me.GetPosition().x > enemy.GetPosition().x)
				{
					me.SetLeftSide(false);
					me.FaceRight(false);
				}
			}
		}
	};
}