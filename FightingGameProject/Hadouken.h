#pragma once
#include <array>
#include "SpecialMove.h"

namespace RB
{
	class Hadouken : public SpecialMove
	{
	private:
		std::array<ConvertedInputType, 4> arr;
		
	public:
		void SetCombo() override
		{
			arr[0] = ConvertedInputType::DOWN;
			arr[1] = ConvertedInputType::DOWN_FORWARD;
			arr[2] = ConvertedInputType::FORWARD;
			arr[3] = ConvertedInputType::WEAK_PUNCH;
		}

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