#pragma once
#define OLC_PGE_APPLICATION 0
#include "olcPixelGameEngine.h"
#include "Timer.h"

namespace RB
{
	class Game : public olc::PixelGameEngine
	{
	private:
		Timer timer;

	public:
		bool OnUserCreate() override
		{
			sAppName = "C++FightingGame";
			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			if (timer.UpdateGame(fElapsedTime, this))
			{
				Clear(olc::VERY_DARK_GREY);

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