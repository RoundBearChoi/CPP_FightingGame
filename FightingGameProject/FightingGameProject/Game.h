#pragma once
#define OLC_PGE_APPLICATION 0
#include "olcPixelGameEngine.h"
#include "Timer.h"
#include "SceneController.h"
#include "GameWindow.h"
#include "Input.h"

namespace RB
{
	class Game : public olc::PixelGameEngine
	{
	private:
		Timer timer;
		SceneController sceneController;
		Input input;

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
			olc::Pixel grayBackground(20, 20, 20);
			Clear(grayBackground);
			input.UpdateInput(this);

			if (timer.UpdateGame(fElapsedTime, this))
			{
				GameData gameData;
				gameData.left = input.Left();
				gameData.right = input.Right();

				sceneController.UpdateCurrentScene(this, gameData);
				sceneController.RenderCurrentScene(true, this);

				//only clear after update
				input.ClearKeyQueues();
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