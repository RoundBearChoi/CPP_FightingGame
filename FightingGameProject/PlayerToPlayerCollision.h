#pragma once
#include "GameObj.h"

namespace RB
{
	class PlayerToPlayerCollision
	{
	private:
		GameObj* _fighter0 = nullptr;
		GameObj* _fighter1 = nullptr;

	public:
		PlayerToPlayerCollision(GameObj* fighter0, GameObj* fighter1)
		{
			_fighter0 = fighter0;
			_fighter1 = fighter1;
		}
	};
}