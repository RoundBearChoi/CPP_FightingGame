#pragma once
#include <array>
#include "SpecialMove.h"

namespace RB
{
	class Hadouken : public SpecialMove
	{
	private:
		std::array<ConvertedInputType, 4> arr = {
			ConvertedInputType::DOWN,
			ConvertedInputType::DOWN_FORWARD,
			ConvertedInputType::FORWARD,
			ConvertedInputType::WEAK_PUNCH
		};
		
	public:
		void Check(InputElement& _inputElement, size_t bufferIndex, ObjData& objData) override
		{
			if (currIndex < arr.size())
			{
				if (!_inputElement.processed)
				{
					ConvertedInputType converted = GetConvert(_inputElement.inputType, objData);

					if (converted == arr[currIndex])
					{
						correctBuffers.push_back(bufferIndex);
						currIndex++;
					}
				}
			}
		}

		bool IsMatching() override
		{
			if (currIndex >= arr.size())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};
}