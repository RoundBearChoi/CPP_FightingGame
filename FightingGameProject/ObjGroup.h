#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "ObjType.h"
#include "GameObj.h"
#include "GameDataFactory.h"
#include "Camera.h"
#include "ColliderData.h"

namespace RB
{
	class ObjGroup
	{
	protected:
		std::vector<GameObj*> vecObjs;
		Camera* _camera = nullptr;

	public:
		std::vector<SlowMotionMessage> vecSlowMotion;
		ColliderData* colliderData = nullptr;

		virtual void UpdateStates() = 0;
		virtual void RenderStates(bool update) = 0;
		virtual void RenderObjPosition() = 0;
		virtual void RenderBoxColliders() = 0;

		virtual bool SetNextState(int32_t _index, State* ptrState);
		virtual size_t GetObjCount();
		virtual size_t GetObjCreationID(size_t index);
		virtual size_t GetOwnerCreationID(size_t index);
		virtual olc::vi2d GetObjWorldPos(size_t index);

		//colliderdata
		//virtual olc::vi2d GetObjBoxColliderWorldPos(size_t index);
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

		virtual ObjData* GetObjData(int32_t index)
		{
			return nullptr;
		}
	};
}