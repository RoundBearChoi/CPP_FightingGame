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
			animationController.status.nTransitionDelay = 8;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetOffsetType(OffsetType::CENTER_CENTER);
			objData.SetSpriteSize({ 368, 384 });

			//objData.objBoxCollider.SetWidth(80);
			//objData.objBoxCollider.SetHeight(60);
			//objData.objBoxCollider.SetQuad();
			//objData.objBoxCollider.UpdateRotation();
		}

		void OnUpdate(ObjData& objData, GameData& gameData) override
		{
			//int32_t speed = Directions::GetForwardSpeed(objData, 2);
			//
			//olc::vi2d pos = objData.GetPosition();
			//pos.x += speed;
			//objData.SetPosition(pos);
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}