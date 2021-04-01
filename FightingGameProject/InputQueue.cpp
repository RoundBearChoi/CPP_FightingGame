#include "InputQueue.h"

namespace RB
{
	InputQueue* InputQueue::ptr = nullptr;

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

	void InputQueue::AddInputs(GameData& gameData, ObjData& p1, ObjData& p2)
	{
		if (QuadruplePress(gameData.key_w, gameData.key_s, gameData.key_a, gameData.key_d))
		{
			//do nothing
		}
		else if (TriplePress(gameData.key_w, gameData.key_s, gameData.key_a, gameData.key_d))
		{
			//do nothing
		}
		else
		{
			//up forward
			if (gameData.key_d && gameData.key_w)
			{
				if (!upforward)
				{
					IF_COUT{ std::cout << "queued upforward" << std::endl; };
					vecP1Inputs.push_back(InputElement(InputType::UP_FORWARD));
					upforward = true;
				}
			}

			//down forward
			if (gameData.key_d && gameData.key_s)
			{
				if (!downforward)
				{
					IF_COUT{ std::cout << "queued downforward" << std::endl; };
					vecP1Inputs.push_back(InputElement(InputType::DOWN_FORWARD));
					downforward = true;
				}
			}

			//down back
			if (gameData.key_s && gameData.key_a)
			{
				if (!downback)
				{
					IF_COUT{ std::cout << "queued downback" << std::endl; };
					vecP1Inputs.push_back(InputElement(InputType::DOWN_BACK));
					downback = true;
				}
			}

			//up back
			if (gameData.key_a && gameData.key_w)
			{
				if (!upback)
				{
					IF_COUT{ std::cout << "queued upback" << std::endl; };
					vecP1Inputs.push_back(InputElement(InputType::UP_BACK));
					upback = true;
				}
			}
		}
		
		//clear for next queue

		//up forward
		if (!gameData.key_d || !gameData.key_w)
		{
			upforward = false;
		}

		//down forward
		if (!gameData.key_d || !gameData.key_s)
		{
			downforward = false;
		}

		//down back
		if (!gameData.key_s || !gameData.key_a)
		{
			downback = false;
		}

		//up back
		if (!gameData.key_a || !gameData.key_w)
		{
			upback = false;
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
}