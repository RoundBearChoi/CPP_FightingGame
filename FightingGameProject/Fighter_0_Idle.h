#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_WalkForward;
	class Fighter_0_WalkBack;
	class Fighter_0_Jab;
	class Fighter_0_Jump_Prep_Vertical;
	class Fighter_0_Jump_Prep_Forward;
	class Fighter_0_Jump_Prep_Back;
	class Fighter_0_Crouch;

	class Fighter_0_Idle : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Idle()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_idle.png");
			animationController.SetColliderFile("BoxColliderData/Fighter_0/fighter_0_idle.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 2000, 200, 5, 1, 5);
			animationController.status.nTransitionDelay = 6;
		}

		void OnEnter() override
		{
			_ownerObj->objData.SetSpriteSize({ 400, 230 });

			_ownerObj->collisionData.objBoxCollider.SetWidth(76);
			_ownerObj->collisionData.objBoxCollider.SetHeight(170);
			_ownerObj->collisionData.objBoxCollider.SetQuad(OffsetType::BOTTOM_CENTER);
			_ownerObj->collisionData.objBoxCollider.UpdateRotation();
		}

		void OnUpdate() override
		{
			UpdateColliderParts();

			PlayerInput p = PlayerInput::Get(_ownerObj->objData.GetPlayerType());
			Directions d = Directions::Get(_ownerObj->objData.IsFacingRight(), p);

			if (p.weakpunch)
			{
				InputData& inputData = *InputData::ptr;
				Key* wp = inputData.GetWeakPunchKey(_ownerObj->objData.GetPlayerType());
				wp->processed = true;

				nextState = State::NewState<Fighter_0_Jab>(_ownerObj);
			}

			else if (d.forward)
			{
				nextState = State::NewState<Fighter_0_WalkForward>(_ownerObj);
			}
			else if (d.back)
			{
				nextState = State::NewState<Fighter_0_WalkBack>(_ownerObj);
			}

			else if (d.up && !d.forward && !d.back)
			{
				nextState = State::NewState<Fighter_0_Jump_Prep_Vertical>(_ownerObj);
			}
			else if (d.up && d.forward)
			{
				nextState = State::NewState<Fighter_0_Jump_Prep_Forward>(_ownerObj);
			}
			else if (d.up && d.back)
			{
				nextState = State::NewState<Fighter_0_Jump_Prep_Back>(_ownerObj);
			}
			else if (d.down && !d.up)
			{
				nextState = State::NewState<Fighter_0_Crouch>(_ownerObj);
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}