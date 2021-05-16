#pragma once
#include <vector>
#include "InputElement.h"
#include "DevSettings.h"

namespace RB
{
	class InputBuffer
	{
	private:
		//player1
		bool p1_upright = false;
		bool p1_downright = false;
		bool p1_downleft = false;
		bool p1_upleft = false;

		bool p1_left = false;
		bool p1_right = false;
		bool p1_up = false;
		bool p1_down = false;

		bool p1_weakpunch = false;

		//player2
		bool p2_upright = false;
		bool p2_downright = false;
		bool p2_downleft = false;
		bool p2_upleft = false;

		bool p2_left = false;
		bool p2_right = false;
		bool p2_up = false;
		bool p2_down = false;

		bool p2_weakpunch = false;

	public:
		static InputBuffer* ptr;

		std::vector<InputElement> vecP1Inputs;
		std::vector<InputElement> vecP2Inputs;

		void AddInputs();
		void Update();
		bool QuadruplePress(Key* up, Key* down, Key* left, Key* right);
		bool TriplePress(Key* up, Key* down, Key* left, Key* right);
		void AddInputBuffer(
			Key* keyUp, Key* keyDown, Key* keyLeft, Key* keyRight,
			Key* keyWeakPunch,
			std::vector<InputElement>& vecBuffer,
			bool& bUpRight, bool& bDownRight, bool& bDownLeft, bool& bUpLeft,
			bool& bLeft, bool& bRight, bool& bUp, bool& bDown,
			bool& bWeakPunch);
	};
}