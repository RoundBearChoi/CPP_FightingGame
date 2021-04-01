#pragma once
#include <vector>
#include "GameData.h"
#include "ObjData.h"
#include "InputElement.h"
#include "DevSettings.h"

namespace RB
{
	class InputQueue
	{
	private:
		bool p1_upforward = false;
		bool p1_downforward = false;
		bool p1_downback = false;
		bool p1_upback = false;

	public:
		static InputQueue* ptr;

		std::vector<InputElement> vecP1Inputs;
		std::vector<InputElement> vecP2Inputs;

		void AddInputs(GameData& gameData, ObjData& p1, ObjData& p2);
		void Update();
		bool QuadruplePress(Key* up, Key* down, Key* left, Key* right);
		bool TriplePress(Key* up, Key* down, Key* left, Key* right);
		void PlayerFacingRight(Key* up, Key* down, Key* left, Key* right, std::vector<InputElement>& vecBuffer, bool& upforward, bool& downforward, bool& downback, bool& upback);
	};
}