#pragma once
#include "Scene.h"
#include "FightersGroup.h"
#include "ProjectileGroup.h"
#include "ProjectileCollision.h"
#include "ImpactEffectsGroup.h"
#include "DamageDetector.h"

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
		DamageDetector* _damageDetector = nullptr;

	public:
		FightScene();
		~FightScene() override;

		void InitScene() override;
		void UpdateScene() override;
		void RenderObjs() override;
		void RenderStates() override;
		void UpdateRenderTiles() override;
	};
}