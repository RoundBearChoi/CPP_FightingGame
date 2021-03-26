#pragma once
#include "Scene.h"
#include "Fighters.h"
#include "Background.h"

//fighter states
#include "Fighter_0_Idle.h"
#include "Fighter_0_WalkForward.h"
#include "Fighter_0_WalkBack.h"
#include "Fighter_0_Jab.h"
#include "Fighter_0_HitReaction_0.h"

#include "Fighter_1_Idle.h"

//background states
#include "Background_Idle_Trees.h"
#include "Background_Idle_Mountains.h"
#include "Background_Idle_Sun.h"

namespace RB
{
	class FightScene : public Scene
	{
	private:
		Fighters fighters;
		Background background;

	public:
		FightScene();
		~FightScene() override;

		void InitScene() override;
		void Update(GameData& gameData) override;
		void RenderObjs() override;
		void RenderStates(bool update) override;
	};
}