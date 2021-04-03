#include "State.h"

namespace RB
{
	std::vector<BoxCollider>& State::GetColliders()
	{
		static std::vector<BoxCollider> defaultVec;
		return defaultVec;
	}
}