#include "ImpactEffectsGroup.h"

namespace RB
{
	ImpactEffectsGroup::ImpactEffectsGroup(Camera* camera)
	{
		_camera = camera;
		ptrAnimationRenderer = new AnimationRenderer(&vecObjs, _camera);
	}

	ImpactEffectsGroup::~ImpactEffectsGroup()
	{
		delete ptrAnimationRenderer;

		if (vecObjs.size() != 0)
		{
			IF_COUT{ std::cout << std::endl; };

			for (size_t i = 0; i < vecObjs.size(); i++)
			{
				if (vecObjs[i] != nullptr)
				{
					IF_COUT{ std::cout << "destructing effect: " << vecObjs[i]->objData.GetCreationID() << std::endl; };
					delete vecObjs[i];
				}
			}

			IF_COUT{ std::cout << std::endl; };
		}
	}

	void ImpactEffectsGroup::UpdateStates()
	{
		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			if (vecObjs[i] != nullptr)
			{
				GameObj& obj = *vecObjs[i];
				State* state = vecObjs[i]->stateController->currentState;

				if (state != nullptr)
				{
					state->RunUpdateProcess();

					size_t end = (size_t)state->animationController.GetTotalTiles() * (size_t)state->animationController.status.nTransitionDelay;

					if (state->updateCount >= end - (size_t)1)
					{
						delete vecObjs[i];
						vecObjs[i] = nullptr;
					}
				}
			}
		}

		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			if (vecObjs[i] == nullptr)
			{
				vecObjs.erase(vecObjs.begin() + i);
				break;
			}
		}
	};

	void ImpactEffectsGroup::RenderObjPosition()
	{

	};

	void ImpactEffectsGroup::RenderStates()
	{
		ptrAnimationRenderer->Update();
	};

	void ImpactEffectsGroup::UpdateSpriteTileIndex()
	{
		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			if (vecObjs[i] != nullptr)
			{
				vecObjs[i]->stateController->currentState->animationController.NextTileIndex();
			}
		}
	}

	void ImpactEffectsGroup::RenderBoxColliders()
	{
	
	};

	void ImpactEffectsGroup::CreateObj(ObjType objType, olc::vi2d startPos)
	{
		GameObj* obj = new GameObj();
		vecObjs.push_back(obj);
		vecObjs.back()->objData.SetCreationID(vecObjs.size());

		if (objType == ObjType::HIT_EFFECT_0)
		{
			obj->stateController->currentState = State::NewState<ImpactEffect_Hit_0>(&obj->objData);
		}

		obj->objData.SetPosition(startPos);
	}
}