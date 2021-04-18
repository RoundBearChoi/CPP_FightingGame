#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_WalkForward : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_WalkForward()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_walk.png");
			animationController.SetColliderFile("Fighter_0/fighter_0_walk.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 2400, 200, 6, 1, 6);
			animationController.status.nTransitionDelay = 5;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });
		}

		void OnUpdate(ObjData& objData, GameData& gameData) override
		{
			UpdateColliderParts();

			PlayerInput p = PlayerInput::Get(objData.GetPlayerType(), gameData);
			Directions d = Directions::Get(objData, p);
			
			if (d.forward)
			{
				int32_t speed = Directions::GetForwardSpeed(objData, 2);

				olc::vi2d pos = objData.GetPosition();
				pos.x += speed;
				objData.SetPosition(pos);
			}
			else
			{
				nextState = State::NewState<Fighter_0_Idle>();
			}
		}

		void OnAnimationUpdate(ObjData& objData, GameData& gameData) override
		{
			//could update on animation
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}