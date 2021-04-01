#include "InputBuffer.h"

namespace RB
{
	InputBuffer* InputBuffer::ptr = nullptr;

	void InputBuffer::AddInputs(GameData& gameData, ObjData& p1, ObjData& p2)
	{
		PlayerBuffer(gameData.key_w, gameData.key_s, gameData.key_a, gameData.key_d, vecP1Inputs, p1_upright, p1_downright, p1_downleft, p1_upleft);
	}

	void InputBuffer::Update()
	{
		for (size_t i = 0; i < vecP1Inputs.size(); i++)
		{
			vecP1Inputs[i].updateCount++;
		}

		for (size_t i = 0; i < vecP2Inputs.size(); i++)
		{
			vecP2Inputs[i].updateCount++;
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
			// ��
			if (up && right)
			{
				if (!upright)
				{
					IF_COUT{ std::cout << "queued upforward" << std::endl; };
					vecBuffer.push_back(InputElement(InputType::UP_RIGHT));
					upright = true;
				}
			}

			// ��
			if (down && right)
			{
				if (!downright)
				{
					IF_COUT{ std::cout << "queued downforward" << std::endl; };
					vecBuffer.push_back(InputElement(InputType::DOWN_RIGHT));
					downright = true;
				}
			}

			// ��
			if (down && left)
			{
				if (!downleft)
				{
					IF_COUT{ std::cout << "queued downback" << std::endl; };
					vecBuffer.push_back(InputElement(InputType::DOWN_LEFT));
					downleft = true;
				}
			}

			// ��
			if (up && left)
			{
				if (!upleft)
				{
					IF_COUT{ std::cout << "queued upback" << std::endl; };
					vecBuffer.push_back(InputElement(InputType::UP_LEFT));
					upleft = true;
				}
			}
		}

		//clear for next queue

		//up forward
		if (!up || !right)
		{
			upright = false;
		}

		//down forward
		if (!down || !right)
		{
			downright = false;
		}

		//down back
		if (!down || !left)
		{
			downleft = false;
		}

		//up back
		if (!up || !left)
		{
			upleft = false;
		}
	}
}