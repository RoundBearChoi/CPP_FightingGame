#pragma once
#include <vector>
#include "GameData.h"
#include "InputType.h"
#include "ObjData.h"

namespace RB
{
	class InputQueue
	{
	public:
		std::vector<InputType> vecP1Inputs;
		std::vector<InputType> vecP2Inputs;

		static InputQueue* ptr;
		void AddInputs(GameData& gameData, ObjData& p1, ObjData& p2);
	};
}