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
			animationController.SetColliderFile("BoxColliderData/Fighter_0/fighter_0_walkback.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 2400, 200, 6, 1, 6);
			animationController.status.nTransitionDelay = 5;
		}

		void OnEnter() override
		{
			_ownerObj->objData.SetSpriteSize({ 400, 230 });
		}

		void OnUpdate() override
		{
			UpdateColliderParts();

			PlayerInput p = PlayerInput::Get(_ownerObj->objData.GetPlayerType());
			Directions d = Directions::Get(_ownerObj->objData.IsFacingRight(), p);

			if (d.up)
			{
				nextState = State::NewState<Fighter_0_Jump_Prep_Back>( _ownerObj);
			}

			else if (d.back)
			{
				int32_t speed = Directions::GetBackSpeed(_ownerObj->objData.IsFacingRight(), 2);

				olc::vi2d pos = _ownerObj->objData.GetPosition();
				pos.x += speed;
				_ownerObj->objData.SetPosition(pos);
			}

			else
			{
				nextState = State::NewState<Fighter_0_Idle>(_ownerObj);
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}