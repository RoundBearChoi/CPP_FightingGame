#pragma once
#include "Scene.h"
#include "FightersGroup.h"
#include "ProjectileGroup.h"
#include "BackgroundGroup.h"
#include "ProjectileCollision.h"
#include "ImpactEffectsGroup.h"
#include "BodyPartCollision.h"

//temp
#include "Fighter_1_Idle.h"
#include "Background_Idle_Trees.h"
#include "Background_Idle_Mountains.h"
#include "Background_Idle_Sun.h"
#include "ImpactEffect_Hit_0.h"

namespace RB
{
	class FightScene : public Scene
	{
	private:
		FightersGroup fighters;
		ProjectileGroup projectiles;
		ImpactEffectsGroup impactEffects;
		BackgroundGroup background;

	public:
		FightScene();
		~FightScene() override;

		void InitScene() override;
		void UpdateScene(GameData& gameData) override;
		void RenderObjs() override;
		void RenderStates(bool update) override;
	};
}