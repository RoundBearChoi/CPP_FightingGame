#pragma once

#include "GameObj.h"
#include "BoxCollider.h"

#include "Fighter_0_Idle.h"
#include "Fighter_0_Jab.h"
#include "Fighter_0_WalkForward.h"
#include "Fighter_0_WalkBack.h"
#include "Fighter_0_HitReaction_Side.h"
#include "Fighter_0_HitReaction_Up.h"
#include "Fighter_0_Hadouken_Fire.h"
#include "Fighter_0_Hadouken_Recover.h"
#include "Fighter_0_Jump_Prep_Vertical.h"
#include "Fighter_0_Jump_Prep_Forward.h"
#include "Fighter_0_Jump_Prep_Back.h"
#include "Fighter_0_Jump_Up_Vertical.h"
#include "Fighter_0_Jump_Up_Forward.h"
#include "Fighter_0_Jump_Up_Back.h"
#include "Fighter_0_Jump_Fall.h"
#include "Fighter_0_Jump_WeakPunch.h"
#include "Fighter_0_Crouch.h"
#include "Fighter_0_Uppercut.h"

namespace RB
{
	class DummySelector
	{
	private:
		std::array<GameObj*, 18> arrObjs;
		std::array<std::vector<BoxCollider>, 18> arrVecs;
		size_t currentIndex = 0;

	public:
		DummySelector()
		{
			for (size_t i = 0; i < arrObjs.size(); i++)
			{
				arrObjs[i] = new GameObj();
			}

			arrObjs[0]->stateController->currentState = State::NewState<Fighter_0_Idle>(&arrObjs[0]->objData);
			arrObjs[1]->stateController->currentState = State::NewState<Fighter_0_Jab>(&arrObjs[1]->objData);
			arrObjs[2]->stateController->currentState = State::NewState<Fighter_0_WalkForward>(&arrObjs[2]->objData);
			arrObjs[3]->stateController->currentState = State::NewState<Fighter_0_WalkBack>(&arrObjs[3]->objData);
			arrObjs[4]->stateController->currentState = State::NewState<Fighter_0_HitReaction_Side>(&arrObjs[4]->objData);
			arrObjs[5]->stateController->currentState = State::NewState<Fighter_0_HitReaction_Up>(&arrObjs[5]->objData);
			arrObjs[6]->stateController->currentState = State::NewState<Fighter_0_Hadouken_Fire>(&arrObjs[6]->objData);
			arrObjs[7]->stateController->currentState = State::NewState<Fighter_0_Hadouken_Recover>(&arrObjs[7]->objData);
			arrObjs[8]->stateController->currentState = State::NewState<Fighter_0_Jump_Prep_Vertical>(&arrObjs[8]->objData);
			arrObjs[9]->stateController->currentState = State::NewState<Fighter_0_Jump_Prep_Forward>(&arrObjs[9]->objData);
			arrObjs[10]->stateController->currentState = State::NewState<Fighter_0_Jump_Prep_Back>(&arrObjs[10]->objData);
			arrObjs[11]->stateController->currentState = State::NewState<Fighter_0_Jump_Up_Vertical>(&arrObjs[11]->objData);
			arrObjs[12]->stateController->currentState = State::NewState<Fighter_0_Jump_Up_Forward>(&arrObjs[12]->objData);
			arrObjs[13]->stateController->currentState = State::NewState<Fighter_0_Jump_Up_Back>(&arrObjs[13]->objData);
			arrObjs[14]->stateController->currentState = State::NewState<Fighter_0_Jump_Fall>(&arrObjs[14]->objData);
			arrObjs[15]->stateController->currentState = State::NewState<Fighter_0_Jump_WeakPunch>(&arrObjs[15]->objData);
			arrObjs[16]->stateController->currentState = State::NewState<Fighter_0_Crouch>(&arrObjs[16]->objData);
			arrObjs[17]->stateController->currentState = State::NewState<Fighter_0_Uppercut>(&arrObjs[17]->objData);

			for (size_t i = 0; i < arrObjs.size(); i++)
			{
				arrObjs[i]->objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
			}

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

				int32_t tiles = obj->stateController->currentState->animationController.TotalTiles();
				ColliderLoader::SetFighterBodyParts(arrVecs[i], tiles);

				std::string colliderFile = obj->stateController->currentState->animationController.GetColliderPath();
				ColliderLoader::LoadColliderData(arrVecs[i], colliderFile);
			}
		}

		void SyncFrames()
		{
			GameObj* obj = Current();
			size_t indexStart = obj->stateController->currentState->animationController.status.nCurrentTile * ColliderLoader::TotalBodyParts();
			
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
			size_t indexStart = obj->stateController->currentState->animationController.status.nCurrentTile * ColliderLoader::TotalBodyParts();

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