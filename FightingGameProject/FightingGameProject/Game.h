#pragma once
#define OLC_PGE_APPLICATION 0
#include "olcPixelGameEngine.h"

namespace RB
{
	class Game : public olc::PixelGameEngine
	{
	private:

	public:
		bool OnUserCreate() override
		{
			sAppName = "ShitFall";
			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			return true;
		}

		void Run()
		{
			if (Construct(1920, 1080, 1, 1))
			{
				Start();
			}
		}
	};
}