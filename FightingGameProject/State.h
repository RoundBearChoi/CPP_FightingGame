#pragma once
#include <iostream>
#include "DevSettings.h"
#include "ObjData.h"
#include "GameData.h"
#include "AnimationController.h"
#include "DebugRenderer.h"
#include "SpriteLoader.h"
#include "PlayerInput.h"
#include "Directions.h"
#include "CollisionStatus.h"
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
		int32_t updateCount = 0;
		AnimationController animationController;
		std::vector<CollisionStatus> vecCollisionStatus;
		std::vector<CreateProjectile> vecCreateProjectiles;

		virtual ~State() {};
		virtual void OnEnter(ObjData& objData, GameData& gameData) = 0;
		virtual void UpdateState(ObjData& objData, GameData& gameData) = 0;
		
		virtual void OnAnimationUpdate(ObjData& objData, GameData& gameData) { /*do nothing*/ };
		virtual std::vector<BoxCollider>& GetColliders();
		virtual std::vector<olc::vi2d>& GetColliderQuads();
		
		size_t GetHash();
		bool IsNew();
		void UpdateColliders();
		void RenderColliderQuads(ObjData& objData, Camera& cam);
		void UnloadColliderData();
		CollisionStatus* GetCollisionStatus();
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