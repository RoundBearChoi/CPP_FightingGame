#pragma once
#include <vector>
#include "GameData.h"
#include "ObjData.h"
#include "InputElement.h"

namespace RB
{
	class InputQueue
	{
	public:
		std::vector<InputElement> vecP1Inputs;
		std::vector<InputElement> vecP2Inputs;

		static InputQueue* ptr;
		void AddInputs(GameData& gameData, ObjData& p1, ObjData& p2);
		void UpdateFrameCount();
	};
}