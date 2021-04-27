#pragma once
#include "ObjGroup.h"

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
		ProjectileGroup();
		~ProjectileGroup();

		void UpdateStates(GameData& gameData) override;
		void RenderObjPosition(Camera& cam) override;
		void RenderStates(Camera& cam, bool update) override;
		void RenderBoxColliders(Camera& cam) override;

		void CreateProjectiles(std::vector<CreateProjectileMessage>& vecSpecs);
	};
}