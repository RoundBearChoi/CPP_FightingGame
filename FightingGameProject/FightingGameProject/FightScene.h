#pragma once
#include "Scene.h"
#include "Fighters.h"
#include "GameWindow.h"

//states for game scene
//#include "BackgroundIdle.h"
//#include "PlayerGameStart.h"
//#include "PlayerIdle.h"
//#include "PlayerMoveLeft.h"
//#include "PlayerMoveRight.h"
//#include "ShitGenerator.h"
//#include "ShitPosition.h"
//#include "ShitMoveDown.h"
//#include "ShitUpSplash.h"
//#include "ShitCenterSplash.h"
//#include "PlayerDeath.h"
//#include "YesOrNo.h"

namespace RB
{
	class FightScene : public Scene
	{
	private:
		Fighters fighters;

	public:
		FightScene(size_t _id)
		{
			IF_COUT{ std::cout << "constructing FightScene:" << _id << std::endl; }

			ID = _id;
		}

		~FightScene() override
		{
			IF_COUT{ std::cout << "destructing FightScene: " << ID << std::endl; }
		}

		void InitScene() override
		{
			olc::vf2d pos0{ -220.0f, 0.0f };
			olc::vf2d pos1{ 220.0f, 0.0f };

			fighters.SetFighterInfo(0, pos0);
			fighters.SetFighterInfo(1, pos1);
		}

		void UpdateScene(olc::PixelGameEngine* ptrEngine, GameData& gameData) override
		{

		}

		void RenderObjPosition(olc::PixelGameEngine* ptrEngine) override
		{
			//camera position
			olc::vf2d camPos = cam.GetPosition();

			//centermark
			olc::vf2d bottom{ 0.0f, 0.0f };
			olc::vf2d top{ 0.0f, -(float)GameWindow::GetHeight() * 0.025f };
			olc::vf2d left{ -10.0f, 0.0f };
			olc::vf2d right{ 10.0f, 0.0f };
			ptrEngine->DrawLine(top + camPos, bottom + camPos, olc::GREEN);
			ptrEngine->DrawLine(bottom + left + camPos, bottom + right + camPos, olc::GREEN);

			//objs
			fighters.RenderObjPosition(ptrEngine, camPos);
		}

		void RenderStates(bool update, olc::PixelGameEngine* ptrEngine) override
		{

		}
	};
}