#pragma once
#include <vector>
#include "BoxCollider.h"
#include "BodyType.h"

namespace RB
{
	class ColliderLoader
	{
	public:
		static int32_t TotalBodyParts()
		{
			return (int32_t)BodyType::RIGHT_FOOT + 1;
		}

		void SetFighterBodyParts(std::vector<BoxCollider>& vecColliders, int32_t frames)
		{

		}
	};
}