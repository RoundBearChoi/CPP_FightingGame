#pragma once
#include "olcPixelGameEngine.h"
#include "InputElement.h"

namespace RB
{
	class GroupComponent
	{
	public:
		virtual void UpdateComponent() {};
		virtual void RenderComponent() {};
	};
}