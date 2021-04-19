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
			animationController.SetColliderFile("Fighter_0/fighter_0_idle.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 2000, 200, 5, 1, 5);
			animationController.status.nTransitionDelay = 6;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });

			objData.objBoxCollider.SetWidth(76);
			objData.objBoxCollider.SetHeight(170);
			objData.objBoxCollider.SetQuad(OffsetType::BOTTOM_CENTER);
			objData.objBoxCollider.UpdateRotation();
		}

		void OnUpdate(ObjData& objData, GameData& gameData) override
		{
			UpdateColliderParts();

			PlayerInput p = PlayerInput::Get(objData.GetPlayerType(), gameData);
			Directions d = Directions::Get(objData.IsFacingRight(), p);

			if (p.weakpunch)
			{
				Key* wp = gameData.GetWeakPunchKey(objData.GetPlayerType());
				wp->processed = true;

				nextState = State::NewState<Fighter_0_Jab>();
			}

			if (d.forward)
			{
				nextState = State::NewState<Fighter_0_WalkForward>();
			}
			else if (d.back)
			{
				nextState = State::NewState<Fighter_0_WalkBack>();
			}

			if (d.up && !d.forward && !d.back)
			{
				nextState = State::NewState<Fighter_0_Jump_Prep_Vertical>();
			}
			else if (d.up && d.forward)
			{
				nextState = State::NewState<Fighter_0_Jump_Prep_Forward>();
			}
			else if (d.up && d.back)
			{
				nextState = State::NewState<Fighter_0_Jump_Prep_Back>();
			}
			else if (d.down && !d.up)
			{
				nextState = State::NewState<Fighter_0_Crouch>();
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}