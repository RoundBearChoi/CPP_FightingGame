#include "ImpactEffectsGroup.h"

namespace RB
{
	ImpactEffectsGroup::~ImpactEffectsGroup()
	{
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

	void ImpactEffectsGroup::UpdateStates(GameData& gameData)
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

					size_t finalFrame = (size_t)(state->animationController.GetTotalTiles() * state->animationController.status.nTransitionDelay);

					if (state->updateCount >= finalFrame - 1)
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

	void ImpactEffectsGroup::RenderObjPosition(Camera& cam)
	{

	};

	void ImpactEffectsGroup::RenderStates(Camera& cam, bool update)
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
	};

	void ImpactEffectsGroup::RenderBoxColliders(Camera& cam)
	{
	
	};

	size_t ImpactEffectsGroup::GetObjCount() { return 0; };
	size_t ImpactEffectsGroup::GetObjCreationID(size_t index) { return 0; };
	olc::vi2d ImpactEffectsGroup::GetObjWorldPos(size_t index) { return { 0, 0 }; };
	olc::vi2d ImpactEffectsGroup::GetObjBoxColliderWorldPos(size_t index) { return { 0, 0 }; };

	std::array<olc::vi2d, 4> ImpactEffectsGroup::GetObjBoxColliderWorldQuad(size_t index)
	{
		std::array<olc::vi2d, 4> arr; return arr;
	};

	void ImpactEffectsGroup::CreateEffect(ImpactEffectType effectType, olc::vi2d startPos)
	{
		creationCount++;
		GameObj* obj = new GameObj(creationCount);
		vecObjs.push_back(obj);

		if (effectType == ImpactEffectType::HIT_0)
		{
			obj->stateController.currentState = State::NewState<ImpactEffect_Hit_0>();
		}

		obj->objData.SetPosition(startPos);
	}
}