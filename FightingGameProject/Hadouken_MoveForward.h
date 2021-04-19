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
			animationController.SetSpritePath("PNG files/Projectiles/hadouken_ball.png");
			animationController.SetParams(SpriteType::PROJECTILES, 78, 46, 1, 1, 1);
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetOffsetType(OffsetType::CENTER_CENTER);
			objData.SetSpriteSize({ 78, 46 });

			objData.objBoxCollider.SetWidth(80);
			objData.objBoxCollider.SetHeight(60);
			objData.objBoxCollider.SetQuad(OffsetType::CENTER_CENTER);
			objData.objBoxCollider.UpdateRotation();
		}

		void OnUpdate(ObjData& objData, GameData& gameData) override
		{
			if (updateCount % 2 == 0)
			{
				int32_t speed = Directions::GetForwardSpeed(objData.IsFacingRight(), 6);

				olc::vi2d pos = objData.GetPosition();
				pos.x += speed;
				objData.SetPosition(pos);
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}