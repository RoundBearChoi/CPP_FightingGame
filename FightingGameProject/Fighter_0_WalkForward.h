#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_WalkForward : public State
	{
	public:
		STATIC_VEC_COLLIDERS;
		STATIC_VEC_COLLIDER_QUADS;

		Fighter_0_WalkForward()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_walk.png");

			animationController.SetParams(SpriteType::FIGHTER_0, 0, 2400, 200, 6, 1, 6);
			animationController.status.nTransitionDelay = 8;
		}

		size_t GetHash() override
		{
			static size_t hash = 0;
			MakeHash(hash);

			return hash;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			UpdateColliders(GetColliders(), GetColliderQuads());

			PlayerInput p = PlayerInput::Get(objData, gameData);
			Directions d = Directions::Get(objData, p);

			if (d.forward)
			{
				olc::vi2d pos = objData.GetPosition();

				if (objData.IsFacingRight())
				{
					pos.x += 1;
				}
				else
				{
					pos.x -= 1;
				}
				
				objData.SetPosition(pos);
			}
			else
			{
				nextState = State::NewState<Fighter_0_Idle>();
			}
		}

		void RenderBoxColliders(ObjData& objData, Camera& cam) override
		{
			std::vector<olc::vi2d> quads = GetColliderQuads();
			RenderColliderQuads(objData, quads, cam);
		}
	};
}