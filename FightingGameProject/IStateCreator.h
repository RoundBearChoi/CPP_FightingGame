#pragma once
#include "State.h"
#include "GameDataFactory.h"
#include "ObjData.h"

namespace RB
{
	class IStateCreator
	{
	public:
		virtual State* Create(GameDataFactory* gameDataFactory, ObjData* objData) = 0;
	};
}