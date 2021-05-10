#pragma once
#define OLC_PGE_APPLICATION 0
#include "olcPixelGameEngine.h"
#include "Timer.h"
#include "SceneController.h"
#include "GameSettings.h"
#include "Input.h"
#include "GameDataFactory.h"

namespace RB
{
	class Game : public olc::PixelGameEngine
	{
	private:
		InputBuffer inputBuffer;
		Timer timer;
		GameDataFactory _gameDataFactory;
		
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

			//setup gamedatafactory dependencies
			_input = new Input(&_gameDataFactory);
			_sceneController = new SceneController(&_gameDataFactory);
			DevSettings::gameDataFactory = &_gameDataFactory;
			GameSettings::gameDataFactory = &_gameDataFactory;

			_sceneController->Load();
			_sceneController->CreateScene(GameSettings::startingScene);

			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			olc::Pixel grayBackground(20, 20, 20);
			Clear(grayBackground);

			_gameDataFactory.ResetGameData();

			_input->UpdateInput();

			if (timer.UpdateTime(fElapsedTime))
			{
				_input->UpdateGameData();

				DevSettings::UpdateDebugBoxSettings();
				GameSettings::UpdateTargetFrame();

				_sceneController->ChangeScene();
				_sceneController->currentScene->cam.Update(*_gameDataFactory.GetGameData());
				_sceneController->currentScene->UpdateScene(*_gameDataFactory.GetGameData());
				_sceneController->currentScene->RenderStates(true);

				//only clear after update
				_input->ClearKeyQueues();

				inputBuffer.Update();
			}
			else
			{
				_sceneController->currentScene->RenderStates(false);
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