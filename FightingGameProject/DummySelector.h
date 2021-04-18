#pragma once

#include "GameObj.h"
#include "BoxCollider.h"

#include "Fighter_0_Idle.h"
#include "Fighter_0_Jab.h"
#include "Fighter_0_WalkForward.h"
#include "Fighter_0_WalkBack.h"
#include "Fighter_0_HitReaction_0.h"
#include "Fighter_0_Hadouken_Fire.h"
#include "Fighter_0_Hadouken_Recover.h"
#include "Fighter_0_Jump_Prep_Vertical.h"
#include "Fighter_0_Jump_Up.h"
#include "Fighter_0_Jump_Fall.h"

namespace RB
{
	class DummySelector
	{
	private:
		std::array<GameObj*, 10> arrObjs;
		std::array<std::vector<BoxCollider>, 10> arrVecs;
		size_t currentIndex = 0;

	public:
		DummySelector()
		{
			for (size_t i = 0; i < arrObjs.size(); i++)
			{
				arrObjs[i] = new GameObj;
			}

			Init<Fighter_0_Idle>(*arrObjs[0]);
			Init<Fighter_0_Jab>(*arrObjs[1]);
			Init<Fighter_0_WalkForward>(*arrObjs[2]);
			Init<Fighter_0_WalkBack>(*arrObjs[3]);
			Init<Fighter_0_HitReaction_0>(*arrObjs[4]);
			Init<Fighter_0_Hadouken_Fire>(*arrObjs[5]);
			Init<Fighter_0_Hadouken_Recover>(*arrObjs[6]);
			Init<Fighter_0_Jump_Prep_Vertical>(*arrObjs[7]);
			Init<Fighter_0_Jump_Up>(*arrObjs[8]);
			Init<Fighter_0_Jump_Fall>(*arrObjs[9]);

			LoadColliders();
		}

		~DummySelector()
		{
			for (size_t i = 0; i < arrObjs.size(); i++)
			{
				delete arrObjs[i];
			}
		}

		GameObj* Current()
		{
			return arrObjs[currentIndex];
		}

		GameObj* Next()
		{
			currentIndex++;

			if (currentIndex >= arrObjs.size())
			{
				currentIndex = 0;
			}

			return arrObjs[currentIndex];
		}

		GameObj* Prev()
		{
			currentIndex--;

			if (currentIndex >= arrObjs.size())
			{
				currentIndex = arrObjs.size() - 1;
			}

			return arrObjs[currentIndex];
		}

		template<class T>
		void Init(GameObj& obj)
		{
			obj.stateController.CreateNewState<T>();
			obj.objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
		}

		std::vector<BoxCollider>& GetCollider()
		{
			return arrVecs[currentIndex];
		}

		void LoadColliders()
		{
			for (size_t i = 0; i < arrVecs.size(); i++)
			{
				GameObj* obj = arrObjs[i];

				arrVecs[i].clear();

				int32_t tiles = obj->stateController.currentState->animationController.TotalTiles();
				ColliderLoader::SetFighterBodyParts(arrVecs[i], tiles);

				std::string colliderFile = obj->stateController.currentState->animationController.GetColliderPath();
				ColliderLoader::LoadColliderData(arrVecs[i], colliderFile);
			}
		}

		void SyncFrames()
		{
			GameObj* obj = Current();
			size_t indexStart = obj->stateController.currentState->animationController.status.nCurrentTile * ColliderLoader::TotalBodyParts();
			
			std::vector<BoxCollider> data;
			data.reserve(ColliderLoader::TotalBodyParts());

			for (size_t i = indexStart; i < indexStart + ColliderLoader::TotalBodyParts(); i++)
			{
				data.push_back(arrVecs[currentIndex][i]);
			}

			_Sync(currentIndex, data);
		}

		void _Sync(size_t index, std::vector<BoxCollider>& _data)
		{
			for (size_t i = 0; i < arrVecs[index].size(); i++)
			{
				size_t r = i % ColliderLoader::TotalBodyParts();
				arrVecs[index][i] = _data[r];
			}
		}

		void SyncAll()
		{
			GameObj* obj = Current();
			size_t indexStart = obj->stateController.currentState->animationController.status.nCurrentTile * ColliderLoader::TotalBodyParts();

			std::vector<BoxCollider> data;
			data.reserve(ColliderLoader::TotalBodyParts());

			for (size_t i = indexStart; i < indexStart + ColliderLoader::TotalBodyParts(); i++)
			{
				data.push_back(arrVecs[currentIndex][i]);
			}

			for (size_t i = 0; i < arrObjs.size(); i++)
			{
				_Sync(i, data);
			}
		}
	};
}