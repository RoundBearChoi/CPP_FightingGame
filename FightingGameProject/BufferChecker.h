#pragma once
#include <vector>
#include "SpecialMove.h"

namespace RB
{
	class BufferChecker
	{
	public:
		static bool Correct(SpecialMove& move, std::vector<InputElement>& vecInputs, GameObj& obj)
		{
			for (size_t i = 0; i < vecInputs.size(); i++)
			{
				move.Check(vecInputs[i], i, obj.objData);
			}

			if (move.IsMatching())
			{
				for (size_t i = 0; i < move.correctBuffers.size(); i++)
				{
					size_t correctIndex = move.correctBuffers[i];

					if (correctIndex < vecInputs.size())
					{
						vecInputs[correctIndex].processed = true;
					}
				}

				return true;
			}

			return false;
		}
	};
}