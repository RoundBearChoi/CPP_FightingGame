#pragma once
#include "State.h"

namespace RB
{
	class Fighter_1_Idle : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_1_Idle()
		{
			animationController.SetSpritePath("PNG files/Fighter_1/fighter_1_idle.png");

			animationController.SetParams(SpriteType::FIGHTER_1, 1080, 180, 6, 1, 6);
			animationController.status.nTransitionDelay = 12;
		}

		void OnEnter() override
		{
			_ownerObj->objData.SetSpriteSize({ 180, 180 });
		}

		void OnUpdate() override
		{

		}
	};
}