#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Start : public State
	{
		void OnEnter(ObjData& objData, GameData& gameData) override
		{

		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			//olc::vi2d pos = objData.GetPosition();
			//pos.x -= 1;
			//objData.SetPosition(pos);
		}
	};
}