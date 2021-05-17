#include "ProjectileGroup.h"

namespace RB
{
	ProjectileGroup::ProjectileGroup(Camera* camera)
	{
		_camera = camera;
		ptrAnimationRenderer = new AnimationRenderer(&vecObjs, _camera);
		
		colliderData = new ColliderData(&vecObjs);
	}

	ProjectileGroup::~ProjectileGroup()
	{
		delete ptrAnimationRenderer;

		delete colliderData;

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
					state->RunUpdateProcess();
				}
			}
		}
	}

	void ProjectileGroup::RenderObjPosition()
	{
		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			if (vecObjs[i] != nullptr)
			{
				vecObjs[i]->objData.objBoxCollider.Render(*_camera, vecObjs[i]->objData.GetPosition(), olc::CYAN);
			}
		}
	}

	void ProjectileGroup::RenderStates(bool update)
	{
		ptrAnimationRenderer->Update();

		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			if (vecObjs[i] != nullptr)
			{
				if (update)
				{
					vecObjs[i]->stateController->currentState->animationController.NextTileIndex();
				}
			}
		}
	}

	void ProjectileGroup::RenderBoxColliders()
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