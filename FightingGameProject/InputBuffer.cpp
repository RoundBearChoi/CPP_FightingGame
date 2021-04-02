#include "InputBuffer.h"

namespace RB
{
	InputBuffer* InputBuffer::ptr = nullptr;

	void InputBuffer::AddInputs(GameData& gameData)
	{
		PlayerBuffer(
			gameData.key_w, gameData.key_s, gameData.key_a, gameData.key_d,
			gameData.key_t,
			vecP1Inputs,
			p1_upright, p1_downright, p1_downleft, p1_upleft,
			p1_left, p1_right, p1_down,
			p1_weakpunch);
	}

	void InputBuffer::Update()
	{
		size_t p1DeleteCount = 0;
		size_t p2DeleteCount = 0;

		for (size_t i = 0; i < vecP1Inputs.size(); i++)
		{
			vecP1Inputs[i].updateCount++;

			if (vecP1Inputs[i].updateCount > 120)
			{
				p1DeleteCount++;
			}
		}

		for (size_t i = 0; i < vecP2Inputs.size(); i++)
		{
			vecP2Inputs[i].updateCount++;
		}

		for (size_t i = 0; i < p1DeleteCount; i++)
		{
			vecP1Inputs.erase(vecP1Inputs.begin());
		}
	}

	bool InputBuffer::QuadruplePress(Key* up, Key* down, Key* left, Key* right)
	{
		if (up && down && left && right) { return true; }
		else { return false; }
	}

	bool InputBuffer::TriplePress(Key* up, Key* down, Key* left, Key* right)
	{
		int32_t count = 0;

		if (up) { count++; }
		if (down) { count++; }
		if (left) { count++; }
		if (right) { count++; }

		if (count >= 3) { return true; }
		else { return false; }
	}

	void InputBuffer::PlayerBuffer(
		Key* keyUp, Key* keyDown, Key* keyLeft, Key* keyRight,
		Key* keyWeakPunch,
		std::vector<InputElement>& vecBuffer,
		bool& bUpRight, bool& bDownRight, bool& bDownLeft, bool& bUpLeft,
		bool& bLeft, bool& bRight, bool& bDown,
		bool& bWeakPunch)
	{
		if (QuadruplePress(keyUp, keyDown, keyLeft, keyRight))
		{
			//do nothing
		}
		else if (TriplePress(keyUp, keyDown, keyLeft, keyRight))
		{
			//do nothing
		}
		else
		{
			// ¢Ö
			if (keyUp && keyRight)
			{
				if (!bUpRight)
				{
					vecBuffer.push_back(InputElement(InputType::UP_RIGHT));
					bUpRight = true;
				}
			}

			// ¢Ù
			if (keyDown && keyRight)
			{
				if (!bDownRight)
				{
					vecBuffer.push_back(InputElement(InputType::DOWN_RIGHT));
					bDownRight = true;
				}
			}

			// ¢×
			if (keyDown && keyLeft)
			{
				if (!bDownLeft)
				{
					vecBuffer.push_back(InputElement(InputType::DOWN_LEFT));
					bDownLeft = true;
				}
			}

			// ¢Ø
			if (keyUp && keyLeft)
			{
				if (!bUpLeft)
				{
					vecBuffer.push_back(InputElement(InputType::UP_LEFT));
					bUpLeft = true;
				}
			}
		}

		//straight left or right

		if (keyLeft && keyRight || !keyLeft && !keyRight)
		{
			// double press: do nothing
		}
		else if (keyLeft)
		{
			if (!bUpLeft && !bDownLeft)
			{
				if (!bLeft)
				{
					bLeft = true;
					vecBuffer.push_back(InputElement(InputType::LEFT));
				}
			}
		}
		else if (keyRight)
		{
			if (!bUpRight && !bDownRight)
			{
				if (!bRight)
				{
					bRight = true;
					vecBuffer.push_back(InputElement(InputType::RIGHT));
				}
			}
		}

		//straight up or down
		if (keyUp && keyDown || !keyUp && !keyDown)
		{
			// double press: do nothing
		}
		else if (keyDown)
		{
			if (!bDownLeft && !bDownRight)
			{
				if (!bDown)
				{
					bDown = true;
					vecBuffer.push_back(InputElement(InputType::DOWN));
				}
			}
		}

		//punch
		if (keyWeakPunch)
		{
			if (!bWeakPunch)
			{
				bWeakPunch = true;
				vecBuffer.push_back(InputElement(InputType::WEAK_PUNCH));
			}
		}

		//clear for next queue
		
		if (!keyUp || !keyRight) { bUpRight = false; } // ¢Ö
		if (!keyDown || !keyRight) { bDownRight = false; } // ¢Ù
		if (!keyDown || !keyLeft) { bDownLeft = false; } // ¢×
		if (!keyUp || !keyLeft) { bUpLeft = false; } // ¢Ø

		if (!keyLeft) { bLeft = false; } // ¡ç
		if (!keyRight) { bRight = false; } // ¡æ

		if (!keyDown) { bDown = false; } // ¡é

		if (!keyWeakPunch) { bWeakPunch = false; }
	}
}