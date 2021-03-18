#pragma once
#include "Scene.h"
#include "Fighters.h"
#include "Background.h"
#include "GameWindow.h"

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