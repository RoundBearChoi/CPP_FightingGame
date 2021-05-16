#include "ProjectileGroup.h"

namespace RB
{
	ProjectileGroup::ProjectileGroup()
	{
		ptrAnimationRenderer = new AnimationRenderer();
	}

	ProjectileGroup::~ProjectileGroup()
	{
		delete ptrAnimationRenderer;

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

	void ProjectileGroup::UpdateStates()
	{
		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			if (vecObjs[i] != nullptr)
			{
				State* state = vecObjs[i]->stateController->currentState;

				if (state != nullptr)
				{
					state->RunUpdateProcess(vecObjs[i]->objData);
				}
			}
		}
	}

	void ProjectileGroup::RenderObjPosition(Camera& cam)
	{
		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			if (vecObjs[i] != nullptr)
			{
				vecObjs[i]->objData.objBoxCollider.Render(cam, vecObjs[i]->objData.GetPosition(), olc::CYAN);
			}
		}
	}

	void ProjectileGroup::RenderStates(Camera& cam, bool update)
	{
		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			if (vecObjs[i] != nullptr)
			{
				ptrAnimationRenderer->Update(*vecObjs[i], cam);

				if (update)
				{
					vecObjs[i]->stateController->currentState->animationController.NextTileIndex();
				}
			}
		}
	}

	void ProjectileGroup::RenderBoxColliders(Camera& cam)
	{

	}

	void ProjectileGroup::CreateProjectiles(std::vector<CreateProjectileMessage>& vecSpecs)
	{
		for (size_t i = 0; i < vecSpecs.size(); i++)
		{
			GameObj* obj = new GameObj();
			vecObjs.push_back(obj);
			vecObjs.back()->objData.SetCreationID(vecObjs.size());

			if (vecSpecs[i].projectileType == ProjectileType::HADOUKEN)
			{
				obj->stateController->currentState = State::NewState<Hadouken_MoveForward>(&obj->objData);
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
		}
	}
}