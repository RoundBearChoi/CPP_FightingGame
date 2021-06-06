#pragma once
#include "Scene.h"
#include "FightersGroup.h"
#include "ProjectileGroup.h"
#include "ImpactEffectsGroup.h"
#include "PlayerToPlayerCollision.h"
#include "MeleeReaction.h"
#include "PlayerToProjectileCollision.h"
#include "ProjectileCollisionReaction.h"

//temp
#include "Fighter_1_Idle.h"

namespace RB
{
	class FightScene : public Scene
	{
	private:
		FightersGroup* _fighters = nullptr;
		ProjectileGroup* _projectiles = nullptr;
		ImpactEffectsGroup* _impactEffects = nullptr;

		PlayerToPlayerCollision* _playerToPlayerCollision = nullptr;
		MeleeReaction* _meleeReaction = nullptr;
		PlayerToProjectileCollision* _playerToProjectileCollision = nullptr;
		ProjectileCollisionReaction* _projectileCollisionReaction = nullptr;

	public:
		FightScene();
		~FightScene() override;

		void InitScene() override;
		void UpdateScene() override;
		void RenderObjs() override;
		void RenderStates() override;
	};
}