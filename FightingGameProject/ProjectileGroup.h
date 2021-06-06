#pragma once
#include "ObjGroup.h"
#include "ProjectilesFixedUpdater.h"
#include "ProjectilesHitStopMessage.h"

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
		void RenderStates() override;

		void RenderObjPosition() override;
		void RenderBoxColliders() override;

		void CreateProjectiles(std::vector<CreateProjectileMessage>& vecSpecs);
	};
}