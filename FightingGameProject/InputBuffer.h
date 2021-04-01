#pragma once
#include <vector>
#include "GameData.h"
#include "ObjData.h"
#include "InputElement.h"
#include "DevSettings.h"

namespace RB
{
	class InputBuffer
	{
	private:
		bool p1_upright = false;
		bool p1_downright = false;
		bool p1_downleft = false;
		bool p1_upleft = false;

	public:
		static InputBuffer* ptr;

		std::vector<InputElement> vecP1Inputs;
		std::vector<InputElement> vecP2Inputs;

		void AddInputs(GameData& gameData, ObjData& p1, ObjData& p2);
		void Update();
		bool QuadruplePress(Key* up, Key* down, Key* left, Key* right);
		bool TriplePress(Key* up, Key* down, Key* left, Key* right);
		void PlayerBuffer(Key* up, Key* down, Key* left, Key* right, std::vector<InputElement>& vecBuffer, bool& upright, bool& downright, bool& downleft, bool& upleft);
	};
}