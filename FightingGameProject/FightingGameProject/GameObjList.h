#pragma once
#include <vector>
#include "GameObj.h"
#include "GameData.h"

namespace RB
{
	class PlayerDeath;
	class ShitCenterSplash;

	class GameObjList
	{
	private:
		std::vector<GameObj*> vecAllObjs;
		std::vector<int> destructedObjIndex;
		size_t objsCreated = 0;

		void CreateObjFromQueue(GameObj* obj)
		{

		}

	public:
		GameObjList()
		{
			IF_COUT{ std::cout << "constructing GameObjTree" << std::endl; }
			
		}

		~GameObjList()
		{
			IF_COUT{ std::cout << "destructing GameObjTree" << std::endl; }

			for (int i = 0; i < vecAllObjs.size(); i++)
			{
				delete vecAllObjs[i];
			}
		}

		void CreateObj()
		{

		}

		void UpdateObjs(GameData& gameData)
		{

		}
	};
}