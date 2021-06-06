#pragma once
#define OLC_PGE_APPLICATION 0
#include "olcPixelGameEngine.h"
#include "Timer.h"
#include "SceneController.h"
#include "GameSettings.h"
#include "Input.h"

namespace RB
{
	class Game : public olc::PixelGameEngine
	{
	private:
		InputBuffer inputBuffer;
		Timer timer;
		
		Input* _input = nullptr;
		SceneController* _sceneController = nullptr;

	public:
		~Game()
		{
			IF_COUT{ std::cout << std::endl; };
			IF_COUT{ std::cout << "destructing Game" << std::endl; };

			delete _input;
			delete _sceneController;
		}

		bool OnUserCreate() override
		{
			sAppName = "C++FightingGame";
		
			InputBuffer::ptr = &inputBuffer;

			_input = new Input();
			_sceneController = new SceneController();

			_sceneController->Load();
			_sceneController->CreateScene(GameSettings::startingScene);

			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			olc::Pixel grayBackground(20, 20, 20);
			Clear(grayBackground);

			InputData::ResetInputData();

			_input->UpdateInput();

			if (timer.UpdateTime(fElapsedTime))
			{
				_input->UpdateGameData();

				DevSettings::UpdateDebugBoxSettings();
				GameSettings::UpdateTargetFrame();

				_sceneController->ChangeScene();
				_sceneController->currentScene->_cam->Update();
				_sceneController->currentScene->UpdateScene();
				_sceneController->currentScene->RenderStates();

				//only update tile indexes on fixed update
				_sceneController->currentScene->UpdateRenderTiles();

				//only clear after update
				_input->ClearKeyQueues();

				inputBuffer.Update();
			}
			else
			{
				_sceneController->currentScene->RenderStates();
			}

			_sceneController->currentScene->RenderObjs();
			timer.ShowUpdateCount();

			if (DevSettings::renderMode == RenderMode::DEBUG_ONLY)
			{
				olc::Renderer::ptrPGE->DrawString({ 0, 28 }, "render mode: debug only");
			}
			else if (DevSettings::renderMode == RenderMode::SPRITES_ONLY)
			{
				olc::Renderer::ptrPGE->DrawString({ 0, 28 }, "render mode: sprites only");
			}
			else if (DevSettings::renderMode == RenderMode::SPRITES_AND_DEBUG)
			{
				olc::Renderer::ptrPGE->DrawString({ 0, 28 }, "render mode: sprites and debug");
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