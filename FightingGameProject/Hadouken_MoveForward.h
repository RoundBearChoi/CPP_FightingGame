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

		void OnEnter() override
		{
			_objData->SetOffsetType(OffsetType::CENTER_CENTER);
			_objData->SetSpriteSize({ 78, 46 });

			_objData->objBoxCollider.SetWidth(80);
			_objData->objBoxCollider.SetHeight(60);
			_objData->objBoxCollider.SetQuad(OffsetType::CENTER_CENTER);
			_objData->objBoxCollider.UpdateRotation();
		}

		void OnUpdate() override
		{
			int32_t speed = Directions::GetForwardSpeed(_objData->IsFacingRight(), 4);

			olc::vi2d pos = _objData->GetPosition();
			pos.x += speed;
			_objData->SetPosition(pos);
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}