#pragma once
#include <array>
#include "GroupComponent.h"

namespace RB
{
	class FighterDirection : public GroupComponent
	{
	public:
		void Update(std::vector<GameObj*>& vecObjs) override
		{
			UpdateFigherDirection(vecObjs[0]->objData, vecObjs[1]->objData);
			UpdateFigherDirection(vecObjs[1]->objData, vecObjs[0]->objData);
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