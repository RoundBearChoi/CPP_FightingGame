#include "InputQueue.h"

namespace RB
{
	InputQueue* InputQueue::ptr = nullptr;

	void InputQueue::AddInputs(GameData& gameData, ObjData& p1, ObjData& p2)
	{

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