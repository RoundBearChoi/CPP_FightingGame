#include "InputQueue.h"

namespace RB
{
	InputQueue* InputQueue::ptr = nullptr;

	void InputQueue::AddInputs(GameData& gameData, ObjData& p1, ObjData& p2)
	{
		bool upforward = false;
		bool downforward = false;
		bool downback = false;
		bool upback = false;

		//up forward
		if (gameData.key_d && gameData.key_w)
		{
			//std::cout << "adding" << std::endl;
			//gameData.key_d->processed = true;
			//gameData.key_w->processed = true;
			vecP1Inputs.push_back(InputElement(InputType::UP_FORWARD));
			upforward = true;
		}

		//down forward
		if (gameData.key_d && gameData.key_s)
		{
			vecP1Inputs.push_back(InputElement(InputType::DOWN_FORWARD));
			downforward = true;
		}

		//down back
		if (gameData.key_s && gameData.key_a)
		{
			vecP1Inputs.push_back(InputElement(InputType::DOWN_BACK));
			downback = true;
		}

		//up back
		if (gameData.key_a && gameData.key_w)
		{
			vecP1Inputs.push_back(InputElement(InputType::UP_BACK));
			upback = true;
		}
	}

	void InputQueue::UpdateFrameCount()
	{
		for (size_t i = 0; i < vecP1Inputs.size(); i++)
		{
			vecP1Inputs[i].frameCount++;
		}

		for (size_t i = 0; i < vecP2Inputs.size(); i++)
		{
			vecP2Inputs[i].frameCount++;
		}
	}
}