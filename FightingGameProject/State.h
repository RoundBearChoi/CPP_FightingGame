#pragma once
#include <iostream>
#include "ObjBase.h"
#include "DevSettings.h"
#include "AnimationController.h"
#include "Directions.h"
#include "CheckCollisionMessage.h"
#include "CreateProjectileMessage.h"

namespace RB
{
	class State
	{
	protected:
		bool isNew = true;
		virtual size_t& Hash();
		void MakeHash(size_t& _hash);
		ObjBase* _ownerObj = nullptr;

	public:
		State* nextState = nullptr;
		size_t stateUpdateCount = 0;
		int32_t bodyCollisionCount = 0;
		int32_t maxBodyCollisions = 0;
		AnimationController animationController;
		std::vector<CheckCollisionMessage> vecCheckCollisions;
		std::vector<CreateProjectileMessage> vecCreateProjectiles;

		virtual ~State();
		virtual void OnEnter() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnAnimationUpdate() {}

		virtual std::vector<BoxCollider>& GetColliders();
		virtual std::vector<olc::vi2d>& GetColliderQuads();
		
		void RunUpdateProcess();
		size_t GetHash();
		bool IsNew();
		void UpdateColliderParts();
		void RenderColliderQuads(Camera& cam);
		void UnloadColliderData();
		CheckCollisionMessage* GetCollisionStatus();
		olc::vi2d GetColliderWorldPos(BodyType _bodyType);
		std::array<olc::vi2d, 4> GetColliderQuadsWorldPos(BodyType _bodyType);

		void SetObjData(ObjBase* ownerObj)
		{
			_ownerObj = ownerObj;
		}

		template<class T>
		static State* NewState(ObjBase* ownerObj)
		{
			if (std::is_base_of<State, T>::value)
			{
				State* state = new T();
				state->SetObjData(ownerObj);
				return state;
			}
			else
			{
				return nullptr;
			}
		}
	};
}