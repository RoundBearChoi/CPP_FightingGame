#pragma once
#include <iostream>
#include "DevSettings.h"
#include "ObjData.h"
#include "GameData.h"
#include "AnimationController.h"
#include "DebugRenderer.h"
#include "Directions.h"
#include "CollisionQueue.h"
#include "CreateProjectile.h"

namespace RB
{
	class State
	{
	protected:
		bool isNew = true;
		virtual size_t& Hash();
		void MakeHash(size_t& _hash);

	public:
		State* nextState = nullptr;
		size_t updateCount = 0;
		int32_t bodyCollisionCount = 0;
		int32_t maxBodyCollisions = 0;
		AnimationController animationController;
		std::vector<CollisionQueue> vecCollisionStatus;
		std::vector<CreateProjectile> vecCreateProjectiles;

		virtual ~State() {};
		virtual void OnEnter(ObjData& objData, GameData& gameData) = 0;
		virtual void OnUpdate(ObjData& objData, GameData& gameData) = 0;
		virtual void OnAnimationUpdate(ObjData& objData, GameData& gameData) { /*do nothing*/ };

		virtual std::vector<BoxCollider>& GetColliders();
		virtual std::vector<olc::vi2d>& GetColliderQuads();
		
		void RunUpdateProcess(ObjData& objData, GameData& gameData);
		size_t GetHash();
		bool IsNew();
		void UpdateColliders();
		void RenderColliderQuads(ObjData& objData, Camera& cam);
		void UnloadColliderData();
		CollisionQueue* GetCollisionStatus();
		olc::vi2d GetColliderWorldPos(BodyType _bodyType, ObjData& objData);
		std::array<olc::vi2d, 4> GetColliderQuadsWorldPos(BodyType _bodyType, ObjData& objData);

		template<class T>
		static State* NewState()
		{
			if (std::is_base_of<State, T>::value)
			{
				return new T();
			}
			else
			{
				return nullptr;
			}
		}
	};
}