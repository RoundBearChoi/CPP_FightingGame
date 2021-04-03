#pragma once
#include "State.h"

namespace RB
{
	class Hadouken_MoveForward : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Hadouken_MoveForward()
		{
			//animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_idle.png");
			//animationController.SetColliderFile("Fighter_0/fighter_0_idle.collider");

			//animationController.SetParams(SpriteType::FIGHTER_0, 2000, 200, 5, 1, 5);
			//animationController.status.nTransitionDelay = 10;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			//objData.SetSpriteSize({ 400, 230 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			//PlayerInput p = PlayerInput::Get(objData, gameData);
			//Directions d = Directions::Get(objData, p);
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}