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

		void UpdateState(GameData& gameData) override
		{
			for (size_t i = 0; i < vecObjs.size(); i++)
			{
				GameObj& obj = *vecObjs[i];
				State* state = vecObjs[i]->stateController.currentState;

				if (state != nullptr)
				{
					if (state->IsNew())
					{
						state->OnEnter(obj.objData, gameData);
					}

					state->UpdateState(obj.objData, gameData);
					state->updateCount++;

					//if (obj.stateController.currentState->animationController.status.nDelayCount == 0)
					//{
					//	state->OnAnimationUpdate(obj.objData, gameData);
					//}
				}
			}
		}

		void RenderObjPosition(Camera& cam) override
		{

		}

		void RenderStates(Camera& cam, bool update) override
		{
			for (size_t i = 0; i < vecObjs.size(); i++)
			{
				SheetRenderer::Render(vecObjs[i], cam);

				if (update)
				{
					vecObjs[i]->stateController.currentState->animationController.NextTileIndex();
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

				vecObjs.push_back(obj);
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