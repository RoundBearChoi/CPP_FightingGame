#pragma once
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
			IF_COUT{ std::cout << "construcing GameObj: " << objData.creationID << std::endl; }
		}

		~GameObj()
		{
			IF_COUT{ std::cout << "destructing GameObj: " << objData.creationID << std::endl; }
		}

		void RenderPosition()
		{

		}
	};
}