#pragma once
#include <array>
#include "GroupComponent.h"

namespace RB
{
	class FighterDirection : public GroupComponent
	{
	private:
		std::vector<GameObj*>* _vecFighters = nullptr;

	public:
		FighterDirection(std::vector<GameObj*>* vecFighters)
		{
			_vecFighters = vecFighters;
		}

		void Update() override
		{
			std::vector<GameObj*>& vec = *_vecFighters;
			UpdateFigherDirection(vec[0]->objData, vec[1]->objData);
			UpdateFigherDirection(vec[1]->objData, vec[0]->objData);
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