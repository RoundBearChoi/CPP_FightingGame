#include "ImpactEffectsGroup.h"

namespace RB
{
	ImpactEffectsGroup::ImpactEffectsGroup(Camera* camera)
	{
		_camera = camera;
		ptrAnimationRenderer = new AnimationRenderer(&_vecObjs, _camera);
	}

	ImpactEffectsGroup::~ImpactEffectsGroup()
	{
		delete ptrAnimationRenderer;

		if (_vecObjs.size() != 0)
		{
			IF_COUT{ std::cout << std::endl; };

			for (size_t i = 0; i < _vecObjs.size(); i++)
			{
				if (_vecObjs[i] != nullptr)
				{
					IF_COUT{ std::cout << "destructing effect: " << _vecObjs[i]->objData.GetCreationID() << std::endl; };
					delete _vecObjs[i];
				}
			}

			IF_COUT{ std::cout << std::endl; };
		}
	}

	void ImpactEffectsGroup::UpdateStates()
	{
		for (size_t i = 0; i < _vecObjs.size(); i++)
		{
			if (_vecObjs[i] != nullptr)
			{
				ObjBase& obj = *_vecObjs[i];
				State* state = _vecObjs[i]->GetCurrentState();

				if (state != nullptr)
				{
					state->RunUpdateProcess();

					size_t end = (size_t)state->animationController.GetTotalTiles() * (size_t)state->animationController.status.nTransitionDelay;

					if (state->stateUpdateCount >= end - (size_t)1)
					{
						delete _vecObjs[i];
						_vecObjs[i] = nullptr;
					}
				}
			}
		}

		for (size_t i = 0; i < _vecObjs.size(); i++)
		{
			if (_vecObjs[i] == nullptr)
			{
				_vecObjs.erase(_vecObjs.begin() + i);
				break;
			}
		}

		UpdateSpriteTileIndex();
	};

	void ImpactEffectsGroup::RenderObjPosition()
	{

	};

	void ImpactEffectsGroup::RenderStates()
	{
		ptrAnimationRenderer->Update();
	};

	void ImpactEffectsGroup::RenderBoxColliders()
	{
	
	};

	void ImpactEffectsGroup::CreateObj(ObjType objType, olc::vi2d startPos)
	{
		ObjBase* obj = new GameObj();
		_vecObjs.push_back(obj);
		_vecObjs.back()->objData.SetCreationID(_vecObjs.size());

		if (objType == ObjType::HIT_EFFECT_0)
		{
			obj->SetCurrentState(State::NewState<ImpactEffect_Hit_0>(obj));
		}

		obj->objData.SetPosition(startPos);
	}
}