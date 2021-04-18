#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Jump_Up : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Jump_Up()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_jump_up.png");
			animationController.SetColliderFile("Fighter_0/fighter_0_jump_up.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 1200, 200, 3, 1, 3);
			animationController.status.nTransitionDelay = 6;
			animationController.status.bPlayOnce = true;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });

			//objData.objBoxCollider.SetWidth(76);
			//objData.objBoxCollider.SetHeight(170);
			//objData.objBoxCollider.SetQuad(OffsetType::BOTTOM_CENTER);
			//objData.objBoxCollider.UpdateRotation();

			objData.CreateJumpProcessor();
			objData.ptrJumpProcessor->SetUpForce(10);
		}

		void OnUpdate(ObjData& objData, GameData& gameData) override
		{
			UpdateColliderParts();


		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}