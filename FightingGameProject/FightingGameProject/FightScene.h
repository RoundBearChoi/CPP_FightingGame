#pragma once
#include "Scene.h"
#include "Fighters.h"
#include "Background.h"
#include "GameWindow.h"

//fighter states
#include "Fighter_0_Start.h"
#include "Fighter_1_Start.h"

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
		FightScene()
		{
			IF_COUT{ std::cout << "constructing FightScene" << std::endl; }
		}

		~FightScene() override
		{
			IF_COUT{ std::cout << "destructing FightScene" << std::endl; }
		}

		void InitScene() override
		{
			fighters.SetFighterInfo(0, { -220, 0 });
			fighters.SetFighterInfo(1, { 220, 0 });

			fighters.SetInitialState<Fighter_0_Start>(0);
			fighters.SetInitialState<Fighter_1_Start>(1);

			background.SetBackgroundInfo(0, { 0, -250 }); //trees
			background.SetBackgroundInfo(1, { 0, -400 }); //mountains
			background.SetBackgroundInfo(2, { 0, -530 }); //sun

			background.SetInitialState<Background_Idle_Trees>(0);
			background.SetInitialState<Background_Idle_Mountains>(1);
			background.SetInitialState<Background_Idle_Sun>(2);
		}

		void Update(GameData& gameData) override
		{
			background.UpdateState(gameData);
			background.UpdateOffset(cam);
			fighters.UpdateState(gameData);
		}

		void RenderObjPosition(olc::PixelGameEngine* ptrEngine) override
		{
			RenderCenterMark(ptrEngine, cam);

			//background.RenderObjPosition(ptrEngine, cam);
			//fighters.RenderObjPosition(ptrEngine, cam);
		}

		void RenderStates(olc::PixelGameEngine* ptrEngine, bool update) override
		{
			background.RenderStates(ptrEngine, ptrDecalLoader, cam, update);
			fighters.RenderStates(ptrEngine, ptrDecalLoader, cam, update);
		}
	};
}