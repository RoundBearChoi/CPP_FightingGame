#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "ObjType.h"
#include "GameObj.h"
#include "GameDataFactory.h"

namespace RB
{
	class ObjGroup
	{
	protected:
		std::vector<GameObj*> vecObjs;
		GameDataFactory* _gameDataFactory = nullptr;

	public:
		std::vector<SlowMotionMessage> vecSlowMotion;

		virtual void UpdateStates(GameData& gameData) = 0;
		virtual void RenderStates(Camera& cam, bool update) = 0;
		virtual bool SetNextState(int32_t _index, State* ptrState);

		virtual void RenderObjPosition(Camera& cam) = 0;
		virtual void RenderBoxColliders(Camera& cam) = 0;

		virtual size_t GetObjCount();
		virtual size_t GetObjCreationID(size_t index);
		virtual size_t GetOwnerCreationID(size_t index);

		virtual olc::vi2d GetObjWorldPos(size_t index);
		virtual olc::vi2d GetObjBoxColliderWorldPos(size_t index);
		virtual std::array<olc::vi2d, 4> GetObjBoxColliderWorldQuad(size_t index);

		virtual olc::vi2d GetBodyWorldPos(int32_t fighterIndex, BodyType bodyType);
		virtual std::array<olc::vi2d, 4> GetBodyWorldQuad(int32_t fighterIndex, BodyType bodyType);

		virtual void CreateObj(ObjType objType, olc::vi2d startPos) {}
		virtual void DeleteObj(size_t index);

		virtual CheckCollisionMessage* GetCheckCollisionMessage(size_t index);
		virtual int32_t GetCollisionCount(int32_t fighterIndex);
		virtual int32_t GetMaxCollisions(int32_t fighterIndex);
		virtual void AddCollisionCount(int32_t fighterIndex);

		virtual void AddJumpProcessor(int32_t index, int32_t upForce, int32_t sideForce) {};
		virtual std::vector<CreateProjectileMessage>* GetProjectileQueues(size_t _index);
		virtual void RenderComponents() {}
	};
}