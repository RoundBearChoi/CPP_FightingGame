#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_WalkForward;
	class Fighter_0_Jab;

	class Fighter_0_Idle : public State
	{
	public:
		STATIC_VEC_COLLIDERS;
		STATIC_VEC_COLLIDER_QUADS;

		Fighter_0_Idle()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_idle.png");

			animationController.SetParams(SpriteType::FIGHTER_0, 0, 2000, 200, 5, 1, 5);
			animationController.status.nTransitionDelay = 10;
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

			if (objData.GetTransitionPermission())
			{
				if (gameData.key_t)
				{
					gameData.key_t->processed = true;
					nextState = State::NewState<Fighter_0_Jab>();
				}

				if (gameData.key_d)
				{
					nextState = State::NewState<Fighter_0_WalkForward>();
				}
			}
		}

		void RenderBoxColliders(ObjData& objData, Camera& cam) override
		{
			std::vector<olc::vi2d> quads = GetColliderQuads();
			int32_t start = animationController.status.nCurrentTile * (4 * ColliderLoader::TotalBodyParts());

			for (size_t i = start; i < start + (4 * ColliderLoader::TotalBodyParts()); i+=4)
			{
				std::array<olc::vi2d, 4>arr;
				arr[0] = RelativeVector::GetPosition(quads[i], cam);
				arr[1] = RelativeVector::GetPosition(quads[i + 1], cam);
				arr[2] = RelativeVector::GetPosition(quads[i + 2], cam);
				arr[3] = RelativeVector::GetPosition(quads[i + 3], cam);

				arr[0] += objData.GetPosition();
				arr[1] += objData.GetPosition();
				arr[2] += objData.GetPosition();
				arr[3] += objData.GetPosition();

				olc::Renderer::ptrPGE->DrawLine(arr[0], arr[1], olc::BLUE);
				olc::Renderer::ptrPGE->DrawLine(arr[1], arr[2], olc::BLUE);
				olc::Renderer::ptrPGE->DrawLine(arr[2], arr[3], olc::BLUE);
				olc::Renderer::ptrPGE->DrawLine(arr[3], arr[0], olc::BLUE);
			}
		}
	};
}