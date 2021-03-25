#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_WalkForward;
	class Fighter_0_WalkBack;
	class Fighter_0_Jab;

	class Fighter_0_Idle : public State
	{
	public:
		Fighter_0_Idle()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_idle.png");
			animationController.SetColliderFile("Fighter_0/fighter_0_idle.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 2000, 200, 5, 1, 5);
			animationController.status.nTransitionDelay = 10;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			UpdateColliders();

			PlayerInput p = PlayerInput::Get(objData, gameData);
			Directions d = Directions::Get(objData, p);

			if (p.weakpunch)
			{
				gameData.key_t->processed = true;
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

		size_t GetHash() override
		{
			static size_t hash = 0;
			MakeHash(hash);
			return hash;
		}
	};
}