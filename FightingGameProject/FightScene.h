#pragma once
#include "Scene.h"
#include "Fighters.h"
#include "Background.h"

//temp
#include "Fighter_1_Idle.h"
#include "Background_Idle_Trees.h"
#include "Background_Idle_Mountains.h"
#include "Background_Idle_Sun.h"

//temp
#include "DecalLineRenderer.h"

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