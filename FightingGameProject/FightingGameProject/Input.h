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

			//arrow key up
			if (ptrEngine->GetKey(olc::Key::UP).bPressed)
			{
				Pressed_Up = true;
				Queued_Up = true;
			}

			if (ptrEngine->GetKey(olc::Key::UP).bReleased)
			{
				Pressed_Up = false;
			}

			//arrow key up
			if (ptrEngine->GetKey(olc::Key::DOWN).bPressed)
			{
				Pressed_Down = true;
				Queued_Down = true;
			}

			if (ptrEngine->GetKey(olc::Key::DOWN).bReleased)
			{
				Pressed_Down = false;
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

		bool Up()
		{
			if (Pressed_Up || Queued_Up)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool Down()
		{
			if (Pressed_Down || Queued_Down)
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