#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "DevSettings.h"

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

		bool bStartGame = false;
		bool bQuitGame = false;

	public:
		void UpdateInput(olc::PixelGameEngine* ptrEngine)
		{
			//arrow key left
			if (ptrEngine->GetKey(olc::Key::LEFT).bPressed)
			{
				Pressed_Left = true;
				Queued_Left = true;
			}
			
			if (ptrEngine->GetKey(olc::Key::LEFT).bReleased)
			{
				Pressed_Left = false;
			}

			//arrow key left
			if (ptrEngine->GetKey(olc::Key::RIGHT).bPressed)
			{
				Pressed_Right = true;
				Queued_Right = true;
			}

			if (ptrEngine->GetKey(olc::Key::RIGHT).bReleased)
			{
				Pressed_Right = false;
			}

			//start
			if (ptrEngine->GetKey(olc::Key::ENTER).bHeld)
			{
				bStartGame = true;
			}
		}

		bool Left()
		{
			if (Pressed_Left || Queued_Left)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool Right()
		{
			if (Pressed_Right || Queued_Right)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void ClearKeyQueues()
		{
			Queued_Left = false;
			Queued_Right = false;
			Queued_Up = false;
			Queued_Down = false;

			bStartGame = false;
		}

		bool StartGame()
		{
			return bStartGame;
		}

		bool IsHeld(olc::PixelGameEngine* ptrEngine, olc::Key targetKey)
		{
			if (ptrEngine->GetKey(targetKey).bHeld)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};
}