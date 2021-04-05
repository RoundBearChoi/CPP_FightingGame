#pragma once
#include "Scene.h"
#include "FightersGroup.h"
#include "ProjectileGroup.h"
#include "BackgroundGroup.h"
#include "InputBuffer.h"
#include "ProjectileCollision.h"

//temp
#include "Fighter_1_Idle.h"
#include "Background_Idle_Trees.h"
#include "Background_Idle_Mountains.h"
#include "Background_Idle_Sun.h"

namespace RB
{
	class FightScene : public Scene
	{
	private:
		FightersGroup fighters;
		ProjectileGroup projectiles;
		BackgroundGroup background;

	public:
		FightScene();
		~FightScene() override;

		void InitScene() override;
		void Update(GameData& gameData) override;
		void RenderObjs() override;
		void RenderStates(bool update) override;
	};
}