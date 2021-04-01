#include "InputQueue.h"

namespace RB
{
	InputQueue* InputQueue::ptr = nullptr;

	void InputQueue::AddInputs(GameData& gameData, ObjData& p1, ObjData& p2)
	{
		if (p1.IsFacingRight())
		{
			PlayerFacingRight(gameData.key_w, gameData.key_s, gameData.key_a, gameData.key_d, vecP1Inputs, p1_upforward, p1_downforward, p1_downback, p1_upback);
		}
	}

	void InputQueue::Update()
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

	bool InputQueue::QuadruplePress(Key* up, Key* down, Key* left, Key* right)
	{
		if (up && down && left && right)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool InputQueue::TriplePress(Key* up, Key* down, Key* left, Key* right)
	{
		int32_t count = 0;

		if (up)
		{
			count++;
		}

		if (down)
		{
			count++;
		}

		if (left)
		{
			count++;
		}

		if (right)
		{
			count++;
		}

		if (count >= 3)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void InputQueue::PlayerFacingRight(Key* up, Key* down, Key* left, Key* right, std::vector<InputElement>& vecBuffer, bool& upforward, bool& downforward, bool& downback, bool& upback)
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
			//up forward
			if (up && right)
			{
				if (!upforward)
				{
					IF_COUT{ std::cout << "queued upforward" << std::endl; };
					vecBuffer.push_back(InputElement(InputType::UP_FORWARD));
					upforward = true;
				}
			}

			//down forward
			if (down && right)
			{
				if (!downforward)
				{
					IF_COUT{ std::cout << "queued downforward" << std::endl; };
					vecBuffer.push_back(InputElement(InputType::DOWN_FORWARD));
					downforward = true;
				}
			}

			//down back
			if (down && left)
			{
				if (!downback)
				{
					IF_COUT{ std::cout << "queued downback" << std::endl; };
					vecBuffer.push_back(InputElement(InputType::DOWN_BACK));
					downback = true;
				}
			}

			//up back
			if (up && left)
			{
				if (!upback)
				{
					IF_COUT{ std::cout << "queued upback" << std::endl; };
					vecBuffer.push_back(InputElement(InputType::UP_BACK));
					upback = true;
				}
			}
		}

		//clear for next queue

		//up forward
		if (!up || !right)
		{
			upforward = false;
		}

		//down forward
		if (!down || !right)
		{
			downforward = false;
		}

		//down back
		if (!down || !left)
		{
			downback = false;
		}

		//up back
		if (!up || !left)
		{
			upback = false;
		}
	}
}