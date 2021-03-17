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
		SceneController sceneController;
		Input input;
		Timer timer;
		
	public:
		~Game()
		{
			IF_COUT{ std::cout << std::endl; }
			IF_COUT{ std::cout << "destructing Game" << std::endl; }
		}

		bool OnUserCreate() override
		{
			sAppName = "C++FightingGame";
			sceneController.CreateScene(SceneType::HITBOX_EDITOR_SCENE);
			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			olc::Pixel grayBackground(20, 20, 20);
			Clear(grayBackground);

			input.UpdateInput();

			if (timer.UpdateGame(fElapsedTime))
			{
				//set gamedata per frame
				GameData gameData;
				input.UpdateGameData(gameData);

				sceneController.currentScene->cam.Update(gameData);
				sceneController.currentScene->Update(gameData);
				sceneController.currentScene->RenderStates(true);

				//only clear after update
				input.ClearKeyQueues();
			}
			else
			{
				sceneController.currentScene->RenderStates(false);
			}

			sceneController.currentScene->RenderObjPosition();
			timer.ShowUpdateCount();

			return true;
		}

		void Run()
		{
			if (Construct(WINDOW_WIDTH, WINDOW_HEIGHT, 1, 1))
			{
				Start();
			}
		}
	};
}