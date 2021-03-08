#pragma once
#include "olcPixelGameEngine.h"
#include "DevSettings.h"
#include "ObjData.h"

namespace RB
{
	class GameObj
	{	
	public:
		ObjData objData;

		GameObj()
		{
			IF_COUT{ std::cout << "construcing GameObj: " << objData.GetCreationID() << std::endl; }
		}

		~GameObj()
		{
			IF_COUT{ std::cout << "destructing GameObj: " << objData.GetCreationID() << std::endl; }
		}

		void RenderPosition(olc::PixelGameEngine* ptrEngine)
		{
			ptrEngine->FillCircle(objData.GetPosition(), 5.0f, olc::RED);
		}
	};
}