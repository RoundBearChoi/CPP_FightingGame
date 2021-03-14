#pragma once
#include <vector>
#include "olcPixelGameEngine.h"

namespace RB
{
	class Input
	{
	private:
		bool Pressed_Left = false;
		bool Pressed_Right = false;
		bool Pressed_Up = false;
		bool Pressed_Down = false;

		bool Queued_Left = false;
		bool Queued_Right = false;
		bool Queued_Up = false;
		bool Queued_Down = false;

	public:
		void UpdateInput()
		{
			UpdateKey(Pressed_Left, Queued_Left, olc::Key::LEFT);
			UpdateKey(Pressed_Right, Queued_Right, olc::Key::RIGHT);
			UpdateKey(Pressed_Up, Queued_Up, olc::Key::UP);
			UpdateKey(Pressed_Down, Queued_Down, olc::Key::DOWN);
		}

		void UpdateKey(bool& pressed, bool& queued, olc::Key targetKey)
		{
			if (olc::Platform::ptrPGE->GetKey(targetKey).bPressed)
			{
				pressed = true;
				queued = true;
			}

			if (olc::Platform::ptrPGE->GetKey(targetKey).bReleased)
			{
				pressed = false;
			}
		}

		void UpdateGameData(GameData& gameData)
		{
			gameData.left = Left();
			gameData.right = Right();
			gameData.up = Up();
			gameData.down = Down();
		}

		bool Left()
		{
			if (Pressed_Left || Queued_Left) { return true; }
			else { return false; }
		}

		bool Right()
		{
			if (Pressed_Right || Queued_Right) { return true; }
			else { return false; }
		}

		bool Up()
		{
			if (Pressed_Up || Queued_Up) { return true; }
			else { return false; }
		}

		bool Down()
		{
			if (Pressed_Down || Queued_Down) { return true; }
			else { return false; }
		}

		void ClearKeyQueues()
		{
			Queued_Left = false;
			Queued_Right = false;
			Queued_Up = false;
			Queued_Down = false;
		}
	};
}