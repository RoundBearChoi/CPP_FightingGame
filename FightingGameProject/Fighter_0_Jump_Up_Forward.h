#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;
	class Fighter_0_Jump_Fall;

	class Fighter_0_Jump_Up_Forward : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Jump_Up_Forward()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_jump_up_forward.png");
			animationController.SetColliderFile("Fighter_0/fighter_0_jump_up_forward.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 1200, 200, 3, 1, 3);
			animationController.status.nTransitionDelay = 6;
			animationController.status.bPlayOnce = true;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });

			objData.CreateJumpProcessor();
			objData.ptrJumpProcessor->SetUpForce(10);
			objData.ptrJumpProcessor->SetHorizontalForce(5);
			objData.ptrJumpProcessor->moveHorizontally = true;
		}

		void OnUpdate(ObjData& objData, GameData& gameData) override
		{
			UpdateColliderParts();

			if (objData.ptrJumpProcessor != nullptr)
			{
				if (objData.ptrJumpProcessor->GetUpForce() <= 0)
				{
					nextState = State::NewState<Fighter_0_Jump_Fall>();
				}
			}

			if (objData.GetPosition().y >= 0 && updateCount != 0)
			{
				nextState = State::NewState<Fighter_0_Idle>();
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}