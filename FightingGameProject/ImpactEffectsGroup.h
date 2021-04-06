#pragma once
#include "ObjGroup.h"
#include "GameObj.h"
#include "ImpactEffectType.h"

namespace RB
{
	class ImpactEffect_Hit_0;

	class ImpactEffectsGroup : public ObjGroup
	{
	private:
		std::vector<GameObj*> vecObjs;
		size_t creationCount = 0;

	public:
		~ImpactEffectsGroup()
		{
			if (vecObjs.size() != 0)
			{
				IF_COUT{ std::cout << std::endl; };

				for (size_t i = 0; i < vecObjs.size(); i++)
				{
					IF_COUT{ std::cout << "destructing effect: " << vecObjs[i]->objData.GetCreationID() << std::endl; };
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
		};

		void RenderObjPosition(Camera& cam) override {};

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
		};

		void RenderBoxColliders(Camera& cam) override {};
		size_t GetObjCount() override { return 0; };
		size_t GetObjCreationID(size_t index) override { return 0; };
		olc::vi2d GetObjWorldPos(size_t index) override { return { 0, 0 }; };
		olc::vi2d GetObjBoxColliderWorldPos(size_t index) override { return { 0, 0 }; };
		std::array<olc::vi2d, 4> GetObjBoxColliderWorldQuad(size_t index) override { std::array<olc::vi2d, 4> arr; return arr; };

		void CreateEffect(ImpactEffectType effectType)
		{
			creationCount++;
			GameObj* obj = new GameObj(creationCount);
			vecObjs.push_back(obj);

			if (effectType == ImpactEffectType::HIT_0)
			{
				obj->stateController.currentState = State::NewState<ImpactEffect_Hit_0>();
			}
		}
	};
}