#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_Jab : public State
	{
	public:
		GET_HASH_OVERRIDE;
		//CLEAR_COLLIDER_DATA;

		Fighter_0_Jab()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_jab.png");
			animationController.SetColliderFile("Fighter_0/fighter_0_jab.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 0, 2400, 200, 6, 1, 6);
			animationController.status.nTransitionDelay = 5;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			UpdateColliders(GetColliders(), GetColliderQuads());

			if (objData.GetAnimationIndex() == 5)
			{
				nextState = State::NewState<Fighter_0_Idle>();
			}
		}

		void RenderBoxColliders(ObjData& objData, Camera& cam) override
		{
			std::vector<olc::vi2d> quads = GetColliderQuads();
			RenderColliderQuads(objData, quads, cam);
		}

		std::vector<BoxCollider>& GetColliders() override
		{
			static std::vector<BoxCollider> vec;
			return vec;
		}

		std::vector<olc::vi2d>& GetColliderQuads() override
		{
			static std::vector<olc::vi2d> vec;
			return vec;
		}
	};
}