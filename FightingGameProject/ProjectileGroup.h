#pragma once
#include "ObjGroup.h"
#include "GameDataFactory.h"

//components
#include "AnimationRenderer.h"

//projectiles
#include "Hadouken_MoveForward.h"

namespace RB
{
	class ProjectileGroup : public ObjGroup
	{
	private:
		AnimationRenderer* ptrAnimationRenderer = nullptr;

	public:
		ProjectileGroup(Camera* camera);
		~ProjectileGroup();

		void UpdateStates() override;
		void RenderStates(bool update) override;

		void RenderObjPosition() override;
		void RenderBoxColliders() override;

		void CreateProjectiles(std::vector<CreateProjectileMessage>& vecSpecs);
	};
}