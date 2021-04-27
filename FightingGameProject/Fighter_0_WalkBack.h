#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;
	class Fighter_0_Jump_Prep_Back;

	class Fighter_0_WalkBack : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_WalkBack()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_walkback.png");
			animationController.SetColliderFile("Fighter_0/fighter_0_walkback.collider");

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
			Directions d = Directions::Get(objData.IsFacingRight(), p);

			if (d.up)
			{
				nextState = State::NewState<Fighter_0_Jump_Prep_Back>();
			}

			else if (d.back)
			{
				int32_t speed = Directions::GetBackSpeed(objData.IsFacingRight(), 2);

				olc::vi2d pos = objData.GetPosition();
				pos.x += speed;
				objData.SetPosition(pos);
			}

			else
			{
				nextState = State::NewState<Fighter_0_Idle>();
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}