#pragma once
#include <iostream>
#include "DevSettings.h"
#include "ObjData.h"
#include "GameDataFactory.h"
#include "AnimationController.h"
#include "Directions.h"
#include "CheckCollisionMessage.h"
#include "CreateProjectileMessage.h"
#include "SlowMotionMessage.h"

namespace RB
{
	class State
	{
	protected:
		bool isNew = true;
		virtual size_t& Hash();
		void MakeHash(size_t& _hash);
		ObjData* _objData = nullptr;

	public:
		State* nextState = nullptr;
		size_t updateCount = 0;
		int32_t bodyCollisionCount = 0;
		int32_t maxBodyCollisions = 0;
		AnimationController animationController;
		std::vector<CheckCollisionMessage> vecCheckCollisions;
		std::vector<CreateProjectileMessage> vecCreateProjectiles;
		std::vector<SlowMotionMessage> vecSlowMotion;

		virtual ~State();
		virtual void OnEnter(ObjData& objData) = 0;
		virtual void OnUpdate(ObjData& objData) = 0;
		virtual void OnAnimationUpdate(ObjData& objData) {}

		virtual std::vector<BoxCollider>& GetColliders();
		virtual std::vector<olc::vi2d>& GetColliderQuads();
		
		void RunUpdateProcess(ObjData& objData);
		size_t GetHash();
		bool IsNew();
		void UpdateColliderParts();
		void RenderColliderQuads(ObjData& objData, Camera& cam);
		void UnloadColliderData();
		CheckCollisionMessage* GetCollisionStatus();
		olc::vi2d GetColliderWorldPos(BodyType _bodyType, ObjData& objData);
		std::array<olc::vi2d, 4> GetColliderQuadsWorldPos(BodyType _bodyType, ObjData& objData);

		void SetObjData(ObjData* objData)
		{
			_objData = objData;
		}

		template<class T>
		static State* NewState()
		{
			if (std::is_base_of<State, T>::value)
			{
				State* state = new T();
				//state->SetObjData(objData);
				return state;
			}
			else
			{
				return nullptr;
			}
		}
	};
}