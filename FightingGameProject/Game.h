#pragma once
#define OLC_PGE_APPLICATION 0
#include "olcPixelGameEngine.h"
#include "Timer.h"
#include "SceneController.h"
#include "GameSettings.h"
#include "Input.h"
#include "InputBuffer.h"

namespace RB
{
	class Game : public olc::PixelGameEngine
	{
	private:
		SceneController sceneController;
		Input input;
		InputBuffer inputBuffer;
		Timer timer;
		
	public:
		~Game()
		{
			IF_COUT{ std::cout << std::endl; };
			IF_COUT{ std::cout << "destructing Game" << std::endl; };
		}

		bool OnUserCreate() override
		{
			sAppName = "C++FightingGame";
			sceneController.Load();
			sceneController.CreateScene(GameSettings::startingScene);
			
			InputBuffer::ptr = &inputBuffer;

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

				DevSettings::UpdateDebugBoxSettings(gameData);
				GameSettings::UpdateTargetFrame(gameData);

				sceneController.ChangeScene(gameData);
				sceneController.currentScene->cam.Update(gameData);
				sceneController.currentScene->Update(gameData);
				sceneController.currentScene->RenderStates(true);

				//only clear after update
				input.ClearKeyQueues();

				inputBuffer.Update();
			}
			else
			{
				sceneController.currentScene->RenderStates(false);
			}

			sceneController.currentScene->RenderObjs();
			timer.ShowUpdateCount();

			if (DevSettings::renderDebugBoxes)
			{
				olc::Renderer::ptrPGE->DrawString({ 0, 14 }, "render mode: debug");
			}

			return true;
		}

		void Run()
		{
			if (Construct(GameSettings::window_width, GameSettings::window_height, 1, 1))
			{
				Start();
			}
		}
	};
}