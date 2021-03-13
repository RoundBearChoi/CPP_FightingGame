#pragma once
#include "olcPixelGameEngine.h"
#include "DevSettings.h"
#include "ObjData.h"
#include "StateController.h"
#include "RelativeVector.h"

namespace RB
{
	class GameObj
	{	
	public:
		ObjData objData;
		StateController stateController;

		GameObj()
		{
			IF_COUT{ std::cout << "construcing GameObj: " << objData.GetCreationID() << std::endl; }
		}

		~GameObj()
		{
			IF_COUT{ std::cout << "destructing GameObj: " << objData.GetCreationID() << std::endl; }
		}

		void RenderPosition(olc::PixelGameEngine* ptrEngine, Camera& cam);
		void RenderSpriteSize(olc::PixelGameEngine* ptrEngine, Camera& cam);
	};
}