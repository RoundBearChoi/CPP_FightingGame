#pragma once
#include "State.h"

namespace RB
{
	class ImpactEffect_Hit_0 : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		ImpactEffect_Hit_0()
		{
			animationController.SetSpritePath("PNG files/ImpactEffects/hiteffect_0.png");
			animationController.SetParams(SpriteType::IMPACT_EFFECTS, 1840, 384, 5, 1, 5);
			animationController.status.nTransitionDelay = 4;
		}

		void OnEnter() override
		{
			_ownerObj->objData.SetOffsetType(OffsetType::CENTER_CENTER);

			float originalWidth = 368.0f;
			float originalHeight = 384.0f;

			int32_t roundedW = (int32_t)std::round(originalWidth * 0.7f);
			int32_t roundedH = (int32_t)std::round(originalHeight * 0.7f);

			_ownerObj->objData.SetSpriteSize({ roundedW, roundedH });
		}

		void OnUpdate() override
		{

		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}