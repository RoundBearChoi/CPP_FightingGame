#pragma once
#include "InputType.h"

namespace RB
{
	class ComboChecker
	{
	protected:
		size_t currIndex = 0;

	public:
		virtual void SetCombo() = 0;
		virtual void Update(const InputType& _input, const ObjData& objData) = 0;
		virtual bool Yes() = 0;
	};
}