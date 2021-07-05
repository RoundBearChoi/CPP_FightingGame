#pragma once
#include <array>
#include "IGroupComponent.h"

namespace RB
{
	class FighterDirection : public IGroupComponent
	{
	private:
		std::vector<ObjBase*>* _vecFighters = nullptr;

	public:
		FighterDirection(std::vector<ObjBase*>* vecFighters)
		{
			_vecFighters = vecFighters;
		}

		void Update() override
		{
			std::vector<ObjBase*>& vec = *_vecFighters;
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