#pragma once
#include <array>
#include "ComboChecker.h"

namespace RB
{
	class Hadouken : public ComboChecker
	{
	private:
		std::array<InputType, 4> arr;
		
	public:
		std::array<size_t, 4> correctBuffers;

		void SetCombo() override
		{
			arr[0] = InputType::DOWN;
			arr[1] = InputType::DOWN_RIGHT;
			arr[2] = InputType::RIGHT;
			arr[3] = InputType::WEAK_PUNCH;
		}

		void Update(const InputElement& _inputElement, const size_t bufferIndex, const ObjData& objData) override
		{
			if (currIndex < arr.size())
			{
				if (!_inputElement.processed)
				{
					if (_inputElement.inputType == arr[currIndex])
					{
						correctBuffers[currIndex] = bufferIndex;
						currIndex++;
					}
				}
			}
		}

		bool Yes() override
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