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
		FightersGroup fighters;
		ProjectileGroup projectiles;
		ImpactEffectsGroup impactEffects;
		DamageDetector* damageDetector = nullptr;

	public:
		FightScene();
		~FightScene() override;

		void InitScene() override;
		void UpdateScene(GameData& gameData) override;
		void RenderObjs() override;
		void RenderStates(bool update) override;

		bool SkipUpdate(ObjGroup& group);
	};
}