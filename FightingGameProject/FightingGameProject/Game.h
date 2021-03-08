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
			//fixed timestep
			if (fAccumulatedTime >= fTargetFrameTime)
			{
				fAccumulatedTime -= fTargetFrameTime;
				fElapsedTime = fTargetFrameTime;
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
	};
}