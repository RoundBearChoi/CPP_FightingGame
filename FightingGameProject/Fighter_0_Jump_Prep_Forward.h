#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Jump_Up;

	class Fighter_0_Jump_Prep_Forward : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Jump_Prep_Forward()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_jump_prep_forward.png");
			animationController.SetColliderFile("Fighter_0/fighter_0_jump_prep_forward.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 400, 200, 1, 1, 1);
			animationController.status.nTransitionDelay = 4;
			animationController.status.bPlayOnce = true;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });

			//objData.objBoxCollider.SetWidth(76);
			//objData.objBoxCollider.SetHeight(170);
			//objData.objBoxCollider.SetQuad(OffsetType::BOTTOM_CENTER);
			//objData.objBoxCollider.UpdateRotation();
		}

		void OnUpdate(ObjData& objData, GameData& gameData) override
		{
			UpdateColliderParts();

			if (updateCount >= 5)
			{
				nextState = State::NewState<Fighter_0_Jump_Up>();
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}