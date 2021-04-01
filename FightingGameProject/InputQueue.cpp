#include "InputQueue.h"

namespace RB
{
	InputQueue* InputQueue::ptr = nullptr;

	void InputQueue::AddInputs(GameData& gameData, ObjData& p1, ObjData& p2)
	{
		if (p1.IsFacingRight())
		{
			P1FacingRight(gameData.key_w, gameData.key_s, gameData.key_a, gameData.key_d);
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

	void InputQueue::P1FacingRight(Key* up, Key* down, Key* left, Key* right)
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
				if (!p1_upforward)
				{
					IF_COUT{ std::cout << "p1 queued upforward" << std::endl; };
					vecP1Inputs.push_back(InputElement(InputType::UP_FORWARD));
					p1_upforward = true;
				}
			}

			//down forward
			if (down && right)
			{
				if (!p1_downforward)
				{
					IF_COUT{ std::cout << "p1 queued downforward" << std::endl; };
					vecP1Inputs.push_back(InputElement(InputType::DOWN_FORWARD));
					p1_downforward = true;
				}
			}

			//down back
			if (down && left)
			{
				if (!p1_downback)
				{
					IF_COUT{ std::cout << "p1 queued downback" << std::endl; };
					vecP1Inputs.push_back(InputElement(InputType::DOWN_BACK));
					p1_downback = true;
				}
			}

			//up back
			if (up && left)
			{
				if (!p1_upback)
				{
					IF_COUT{ std::cout << "p1 queued upback" << std::endl; };
					vecP1Inputs.push_back(InputElement(InputType::UP_BACK));
					p1_upback = true;
				}
			}
		}

		//clear for next queue

		//up forward
		if (!up || !right)
		{
			p1_upforward = false;
		}

		//down forward
		if (!down || !right)
		{
			p1_downforward = false;
		}

		//down back
		if (!down || !left)
		{
			p1_downback = false;
		}

		//up back
		if (!up || !left)
		{
			p1_upback = false;
		}
	}
}