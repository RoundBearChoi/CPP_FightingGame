#include "InputBuffer.h"

namespace RB
{
	InputBuffer* InputBuffer::ptr = nullptr;

	void InputBuffer::AddInputs(GameData& gameData)
	{
		PlayerBuffer(gameData.key_w, gameData.key_s, gameData.key_a, gameData.key_d, vecP1Inputs, p1_upright, p1_downright, p1_downleft, p1_upleft);
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

	void InputBuffer::PlayerBuffer(Key* up, Key* down, Key* left, Key* right, std::vector<InputElement>& vecBuffer, bool& upright, bool& downright, bool& downleft, bool& upleft)
	{
		if (QuadruplePress(up, down, left, right))
		{
			//do nothing
		}
		else if (TriplePress(up, down, left, right))
		{
			//do nothing
		}
		else
		{
			// ¢Ö
			if (up && right)
			{
				if (!upright)
				{
					vecBuffer.push_back(InputElement(InputType::UP_RIGHT));
					upright = true;
				}
			}

			// ¢Ù
			if (down && right)
			{
				if (!downright)
				{
					vecBuffer.push_back(InputElement(InputType::DOWN_RIGHT));
					downright = true;
				}
			}

			// ¢×
			if (down && left)
			{
				if (!downleft)
				{
					vecBuffer.push_back(InputElement(InputType::DOWN_LEFT));
					downleft = true;
				}
			}

			// ¢Ø
			if (up && left)
			{
				if (!upleft)
				{
					vecBuffer.push_back(InputElement(InputType::UP_LEFT));
					upleft = true;
				}
			}
		}

		//clear for next queue

		// ¢Ö
		if (!up || !right)
		{
			upright = false;
		}

		// ¢Ù
		if (!down || !right)
		{
			downright = false;
		}

		// ¢×
		if (!down || !left)
		{
			downleft = false;
		}

		// ¢Ø
		if (!up || !left)
		{
			upleft = false;
		}
	}
}