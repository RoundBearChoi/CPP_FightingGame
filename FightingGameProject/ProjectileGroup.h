#pragma once
#include "ObjGroup.h"
#include "GameObj.h"

namespace RB
{
	class ProjectileGroup : public ObjGroup
	{
	private:
		std::vector<GameObj*> vecObjs;
		size_t creationCount = 0;

	public:
		~ProjectileGroup()
		{
			if (vecObjs.size() != 0)
			{
				IF_COUT{ std::cout << std::endl; };

				for (size_t i = 0; i < vecObjs.size(); i++)
				{
					IF_COUT{ std::cout << "destructing projectile: " << vecObjs[i]->objData.GetCreationID() << std::endl; };
					delete vecObjs[i];
				}

				IF_COUT{ std::cout << std::endl; };
			}
		}

		void UpdateState(GameData& gameData) override
		{

		}

		void RenderObjPosition(Camera& cam) override
		{

		}

		void RenderStates(Camera& cam, bool update) override
		{

		}

		void RenderBoxColliders(Camera& cam) override
		{

		}

		void CreateProjectiles(std::vector<CreateProjectile>& vecSpecs)
		{
			for (size_t i = 0; i < vecSpecs.size(); i++)
			{
				vecObjs.push_back(_Create());
			}
		}

		GameObj* _Create()
		{
			GameObj* obj = new GameObj();
			creationCount++;
			obj->objData.SetCreationID(creationCount);
			return obj;
		}
	};
}