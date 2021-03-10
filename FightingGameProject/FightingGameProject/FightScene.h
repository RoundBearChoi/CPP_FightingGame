#pragma once
#include "Scene.h"
#include "Fighters.h"
#include "GameWindow.h"

#include "Fighter_0_Start.h"
#include "Fighter_1_Start.h"

namespace RB
{
	class FightScene : public Scene
	{
	private:
		Fighters fighters;

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
			olc::vi2d pos0{ -220, 0 };
			olc::vi2d pos1{ 220, 0 };

			fighters.SetFighterInfo(0, pos0);
			fighters.SetFighterInfo(1, pos1);

			fighters.SetInitialState<Fighter_0_Start>(0);
			fighters.SetInitialState<Fighter_1_Start>(1);
		}

		void UpdateScene(GameData& gameData) override
		{
			cam.Update(gameData);
			fighters.UpdateState(gameData);
		}

		void RenderObjPosition(olc::PixelGameEngine* ptrEngine) override
		{
			olc::vi2d camPos = cam.GetPosition();
			float zoomScale = cam.GetZoom();

			RenderCenterMark(ptrEngine, camPos, zoomScale);

			fighters.RenderObjPosition(ptrEngine, camPos, zoomScale);
		}

		void RenderStates(olc::PixelGameEngine* ptrEngine, bool update) override
		{
			olc::vi2d camPos = cam.GetPosition();
			float zoomScale = cam.GetZoom();

			fighters.RenderStates(ptrEngine, ptrDecalLoader, camPos, zoomScale, update);
		}
	};
}