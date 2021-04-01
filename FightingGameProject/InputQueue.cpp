#include "InputQueue.h"

namespace RB
{
	InputQueue* InputQueue::ptr = nullptr;

	void InputQueue::AddInputs(GameData& gameData, ObjData& p1, ObjData& p2)
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
		else
		{
			upforward = false;
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
		else
		{
			downforward = false;
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
		else
		{
			downback = false;
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
		else
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