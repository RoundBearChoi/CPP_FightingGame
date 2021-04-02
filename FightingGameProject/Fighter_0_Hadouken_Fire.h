#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_Hadouken_Fire : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Hadouken_Fire()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_hadouken_fire.png");
			animationController.SetColliderFile("Fighter_0/fighter_0_hadouken_fire.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 1600, 200, 4, 1, 4);
			animationController.status.nTransitionDelay = 8;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			UpdateColliders();

		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}