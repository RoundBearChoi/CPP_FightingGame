#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_HitReaction_Side : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_HitReaction_Side()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_hitreaction_side.png");
			animationController.SetColliderFile("Fighter_0/fighter_0_hitreaction_side.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 400, 200, 1, 1, 1);
			animationController.status.nTransitionDelay = 8;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });
		}

		void OnUpdate(ObjData& objData, GameData& gameData) override
		{
			UpdateColliderParts();

			if (updateCount == 0 && updateCount < animationController.status.nTransitionDelay * 1)
			{
				int32_t speed = Directions::GetBackSpeed(objData.IsFacingRight(), 2);
				olc::vi2d pos = objData.GetPosition();
				pos.x += speed;
				objData.SetPosition(pos);
			}
			else if (updateCount < animationController.status.nTransitionDelay * 2)
			{
				int32_t speed = Directions::GetBackSpeed(objData.IsFacingRight(), 1);
				olc::vi2d pos = objData.GetPosition();
				pos.x += speed;
				objData.SetPosition(pos);
			}
			else if (updateCount >= animationController.status.nTransitionDelay * 3)
			{
				nextState = State::NewState<Fighter_0_Idle>();
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}