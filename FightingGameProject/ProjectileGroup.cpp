#include "ProjectileGroup.h"

namespace RB
{
	ProjectileGroup::ProjectileGroup(Camera* camera)
	{
		_camera = camera;
		ptrAnimationRenderer = new AnimationRenderer(&_vecObjs, _camera);
		
		_updater = new ProjectilesFixedUpdater(this);

		ProjectilesHitStopMessage::SetReceiver(_updater);
	}

	ProjectileGroup::~ProjectileGroup()
	{
		delete ptrAnimationRenderer;
		delete _updater;

		if (_vecObjs.size() != 0)
		{
			IF_COUT{ std::cout << std::endl; };

			for (size_t i = 0; i < _vecObjs.size(); i++)
			{
				IF_COUT{ std::cout << "destructing projectile: " << _vecObjs[i]->objData.GetCreationID() << std::endl; };
				delete _vecObjs[i];
			}

			IF_COUT{ std::cout << std::endl; };
		}
	}

	void ProjectileGroup::UpdateStates()
	{
		_updater->CustomUpdate();
	}

	void ProjectileGroup::RenderObjPosition()
	{
		for (size_t i = 0; i < _vecObjs.size(); i++)
		{
			if (_vecObjs[i] != nullptr)
			{
				_vecObjs[i]->objData.objBoxCollider.Render(*_camera, _vecObjs[i]->objData.GetPosition(), olc::CYAN);
			}
		}
	}

	void ProjectileGroup::RenderStates()
	{
		ptrAnimationRenderer->Update();
	}

	void ProjectileGroup::RenderBoxColliders()
	{

	}

	void ProjectileGroup::CreateProjectiles(std::vector<CreateProjectileMessage>& vecSpecs)
	{
		for (size_t i = 0; i < vecSpecs.size(); i++)
		{
			ObjBase* obj = new GameObj();
			_vecObjs.push_back(obj);
			_vecObjs.back()->objData.SetCreationID(_vecObjs.size());

			if (vecSpecs[i].projectileType == ProjectileType::HADOUKEN)
			{
				obj->SetCurrentState(State::NewState<Hadouken_MoveForward>(obj));
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