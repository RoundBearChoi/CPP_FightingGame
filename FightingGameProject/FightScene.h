#pragma once
#include "Scene.h"
#include "FightersGroup.h"
#include "ProjectileGroup.h"
#include "ProjectileCollision.h"
#include "ImpactEffectsGroup.h"
#include "BodyPartCollision.h"
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
		DamageDetector* damageDetector = nullptr;

	public:
		FightScene(GameDataFactory* gameDataFactory, StateFactory* stateFactory);
		~FightScene() override;

		void InitScene() override;
		void UpdateScene() override;
		void RenderObjs() override;
		void RenderStates(bool update) override;

		bool SkipUpdate(ObjGroup& group);
	};
}