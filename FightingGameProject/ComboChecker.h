#pragma once
#include "InputElement.h"
#include "ConvertedInputType.h"

namespace RB
{
	class ComboChecker
	{
	protected:
		size_t currIndex = 0;

	public:
		virtual void SetCombo() = 0;
		virtual void Check(InputElement& _inputElement, size_t bufferIndex, ObjData& objData) = 0;
		virtual bool Yes() = 0;

		ConvertedInputType GetConvert(InputType& _inputType, ObjData& objData)
		{
			if (_inputType == InputType::UP)
			{
				return ConvertedInputType::UP;
			}
			else if (_inputType == InputType::DOWN)
			{
				return ConvertedInputType::DOWN;
			}

			if (_inputType == InputType::WEAK_PUNCH)
			{
				return ConvertedInputType::WEAK_PUNCH;
			}

			if (objData.IsFacingRight())
			{
				switch (_inputType)
				{
				case InputType::LEFT:
					return ConvertedInputType::BACK;
				case InputType::RIGHT:
					return ConvertedInputType::FORWARD;

				case InputType::UP_RIGHT:
					return ConvertedInputType::UP_FORWARD;
				case InputType::DOWN_RIGHT:
					return ConvertedInputType::DOWN_FORWARD;
				case InputType::DOWN_LEFT:
					return ConvertedInputType::DOWN_BACK;
				case InputType::UP_LEFT:
					return ConvertedInputType::UP_BACK;
				}
			}
			else
			{
				switch (_inputType)
				{
				case InputType::LEFT:
					return ConvertedInputType::FORWARD;
				case InputType::RIGHT:
					return ConvertedInputType::BACK;

				case InputType::UP_RIGHT:
					return ConvertedInputType::UP_BACK;
				case InputType::DOWN_RIGHT:
					return ConvertedInputType::DOWN_BACK;
				case InputType::DOWN_LEFT:
					return ConvertedInputType::DOWN_FORWARD;
				case InputType::UP_LEFT:
					return ConvertedInputType::UP_FORWARD;
				}
			}

			return ConvertedInputType::NONE;
		}
	};
}