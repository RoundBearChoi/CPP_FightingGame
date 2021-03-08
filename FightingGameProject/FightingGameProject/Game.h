#pragma once
#define OLC_PGE_APPLICATION 0
#include "olcPixelGameEngine.h"
#include "Timer.h"
#include "SceneController.h"
#include "GameWindow.h"

namespace RB
{
	class Game : public olc::PixelGameEngine
	{
	private:
		Timer timer;
		SceneController sceneController;

	public:
		~Game()
		{
			IF_COUT{ std::cout << std::endl; }
			IF_COUT{ std::cout << "destructing Game" << std::endl; }
		}

		bool OnUserCreate() override
		{
			sAppName = "C++FightingGame";
			sceneController.CreateScene(SceneType::FIGHT_SCENE);
			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			Clear(olc::VERY_DARK_GREY);

			if (timer.UpdateGame(fElapsedTime, this))
			{
				GameData gameData;
				sceneController.UpdateCurrentScene(this, gameData);
				sceneController.RenderCurrentScene(true, this);
			}
			else
			{
				sceneController.RenderCurrentScene(false, this);
			}

			timer.ShowUpdateCount(this);

			return true;
		}

		void Run()
		{
			if (Construct(GameWindow::GetWidth(), GameWindow::GetHeight(), 1, 1))
			{
				Start();
			}
		}
	};
}