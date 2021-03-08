#pragma once
#define OLC_PGE_APPLICATION 0
#include "olcPixelGameEngine.h"

namespace RB
{
	class Game : public olc::PixelGameEngine
	{
	private:
		float fTargetFrameTime = 1.0f / 120.0f; // target fixed timestep
		float fAccumulatedTime = 0.0f;

	public:
		bool OnUserCreate() override
		{
			sAppName = "C++FightingGame";
			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			if (UpdateGame())
			{

			}

			return true;
		}

		void Run()
		{
			if (Construct(854, 480, 1, 1))
			{
				Start();
			}
		}

		bool UpdateGame()
		{
			//fixed timestep
			if (fAccumulatedTime >= fTargetFrameTime)
			{
				fAccumulatedTime -= fTargetFrameTime;

				return true;
			}
			else
			{
				return false;
			}
		}
	};
}