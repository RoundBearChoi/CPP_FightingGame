#pragma once
#include "InputElement.h"

namespace RB
{
	class ComboChecker
	{
	protected:
		size_t currIndex = 0;

	public:
		virtual void SetCombo() = 0;
		virtual void Update(const InputElement& _inputElement, const size_t bufferIndex, const ObjData& objData) = 0;
		virtual bool Yes() = 0;
	};
}