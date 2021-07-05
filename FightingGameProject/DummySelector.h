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
		std::array<ObjBase*, 18> arrObjs;
		std::array<std::vector<BoxCollider>, 18> arrVecs;
		size_t currentIndex = 0;

	public:
		DummySelector()
		{
			for (size_t i = 0; i < arrObjs.size(); i++)
			{
				arrObjs[i] = new GameObj();
			}

			arrObjs[0]->SetCurrentState(State::NewState<Fighter_0_Idle>(arrObjs[0]));
			arrObjs[1]->SetCurrentState(State::NewState<Fighter_0_Jab>(arrObjs[1]));
			arrObjs[2]->SetCurrentState(State::NewState<Fighter_0_WalkForward>(arrObjs[2]));
			arrObjs[3]->SetCurrentState(State::NewState<Fighter_0_WalkBack>(arrObjs[3]));
			arrObjs[4]->SetCurrentState(State::NewState<Fighter_0_HitReaction_Side>(arrObjs[4]));
			arrObjs[5]->SetCurrentState(State::NewState<Fighter_0_HitReaction_Up>(arrObjs[5]));
			arrObjs[6]->SetCurrentState(State::NewState<Fighter_0_Hadouken_Fire>(arrObjs[6]));
			arrObjs[7]->SetCurrentState(State::NewState<Fighter_0_Hadouken_Recover>(arrObjs[7]));
			arrObjs[8]->SetCurrentState(State::NewState<Fighter_0_Jump_Prep_Vertical>(arrObjs[8]));
			arrObjs[9]->SetCurrentState(State::NewState<Fighter_0_Jump_Prep_Forward>(arrObjs[9]));
			arrObjs[10]->SetCurrentState(State::NewState<Fighter_0_Jump_Prep_Back>(arrObjs[10]));
			arrObjs[11]->SetCurrentState(State::NewState<Fighter_0_Jump_Up_Vertical>(arrObjs[11]));
			arrObjs[12]->SetCurrentState(State::NewState<Fighter_0_Jump_Up_Forward>(arrObjs[12]));
			arrObjs[13]->SetCurrentState(State::NewState<Fighter_0_Jump_Up_Back>(arrObjs[13]));
			arrObjs[14]->SetCurrentState(State::NewState<Fighter_0_Jump_Fall>(arrObjs[14]));
			arrObjs[15]->SetCurrentState(State::NewState<Fighter_0_Jump_WeakPunch>(arrObjs[15]));
			arrObjs[16]->SetCurrentState(State::NewState<Fighter_0_Crouch>(arrObjs[16]));
			arrObjs[17]->SetCurrentState(State::NewState<Fighter_0_Uppercut>(arrObjs[17]));

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

		ObjBase* Current()
		{
			return arrObjs[currentIndex];
		}

		ObjBase* Next()
		{
			currentIndex++;

			if (currentIndex >= arrObjs.size())
			{
				currentIndex = 0;
			}

			return arrObjs[currentIndex];
		}

		ObjBase* Prev()
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
				ObjBase* obj = arrObjs[i];

				arrVecs[i].clear();

				int32_t tiles = obj->GetCurrentState()->animationController.TotalTiles();
				ColliderLoader::SetFighterBodyParts(arrVecs[i], tiles);

				std::string colliderFile = obj->GetCurrentState()->animationController.GetColliderPath();
				ColliderLoader::LoadColliderData(arrVecs[i], colliderFile);
			}
		}

		void SyncFrames()
		{
			ObjBase* obj = Current();
			size_t indexStart = obj->GetCurrentState()->animationController.status.nCurrentTile * ColliderLoader::TotalBodyParts();
			
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
			ObjBase* obj = Current();
			size_t indexStart = obj->GetCurrentState()->animationController.status.nCurrentTile * ColliderLoader::TotalBodyParts();

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