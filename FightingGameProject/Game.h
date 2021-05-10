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
		SceneController sceneController;
		InputBuffer inputBuffer;
		Timer timer;
		GameDataFactory _gameDataFactory;
		
		Input* _input = nullptr;

	public:
		~Game()
		{
			IF_COUT{ std::cout << std::endl; };
			IF_COUT{ std::cout << "destructing Game" << std::endl; };

			delete _input;
		}

		bool OnUserCreate() override
		{
			sAppName = "C++FightingGame";
			sceneController.Load();
			sceneController.CreateScene(GameSettings::startingScene);
			
			InputBuffer::ptr = &inputBuffer;

			//setup gamedatafactory dependencies
			_input = new Input(&_gameDataFactory);
			DevSettings::gameDataFactory = &_gameDataFactory;

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
				GameSettings::UpdateTargetFrame(*_gameDataFactory.GetGameData());

				sceneController.ChangeScene(*_gameDataFactory.GetGameData());
				sceneController.currentScene->cam.Update(*_gameDataFactory.GetGameData());
				sceneController.currentScene->UpdateScene(*_gameDataFactory.GetGameData());
				sceneController.currentScene->RenderStates(true);

				//only clear after update
				_input->ClearKeyQueues();

				inputBuffer.Update();
			}
			else
			{
				sceneController.currentScene->RenderStates(false);
			}

			sceneController.currentScene->RenderObjs();
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