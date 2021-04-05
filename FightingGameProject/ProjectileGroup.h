#pragma once
#include "ObjGroup.h"
#include "GameObj.h"

//projectiles
#include "Hadouken_MoveForward.h"

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

		void UpdateStates(GameData& gameData) override
		{
			for (size_t i = 0; i < vecObjs.size(); i++)
			{
				if (vecObjs[i] != nullptr)
				{
					GameObj& obj = *vecObjs[i];
					State* state = vecObjs[i]->stateController.currentState;

					if (state != nullptr)
					{
						state->RunUpdateProcess(vecObjs[i]->objData, gameData);
					}
				}
			}
		}

		void RenderObjPosition(Camera& cam) override
		{
			for (size_t i = 0; i < vecObjs.size(); i++)
			{
				if (vecObjs[i] != nullptr)
				{
					vecObjs[i]->objData.objBoxCollider.Render(cam, vecObjs[i]->objData.GetPosition(), olc::CYAN);
				}
			}
		}

		void RenderStates(Camera& cam, bool update) override
		{
			for (size_t i = 0; i < vecObjs.size(); i++)
			{
				if (vecObjs[i] != nullptr)
				{
					SheetRenderer::Render(vecObjs[i], cam);

					if (update)
					{
						vecObjs[i]->stateController.currentState->animationController.NextTileIndex();
					}
				}
			}
		}

		void RenderBoxColliders(Camera& cam) override
		{

		}

		void CreateProjectiles(std::vector<CreateProjectile>& vecSpecs)
		{
			for (size_t i = 0; i < vecSpecs.size(); i++)
			{
				GameObj* obj = _Create();

				if (vecSpecs[i].projectileType == ProjectileType::HADOUKEN)
				{
					obj->stateController.currentState = State::NewState<Hadouken_MoveForward>();
				}

				if (vecSpecs[i].forward.x < 0)
				{
					obj->objData.FaceRight(false);
				}
				else if (vecSpecs[i].forward.x > 0)
				{
					obj->objData.FaceRight(true);
				}

				obj->objData.SetPosition(vecSpecs[i].startPos);
				obj->objData.SetOwnerID(vecSpecs[i].ownerObjCreationID);

				vecObjs.push_back(obj);
			}
		}

		size_t GetObjCount() override
		{
			return vecObjs.size();
		}

		GameObj* _Create()
		{
			creationCount++;
			GameObj* obj = new GameObj(creationCount);
			return obj;
		}
	};
}