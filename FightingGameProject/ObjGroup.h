#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "ObjType.h"
#include "GameObj.h"
#include "GameDataFactory.h"
#include "Camera.h"
#include "ColliderData.h"
#include "CollisionData.h"
#include "JumpAdder.h"
#include "MessageGetter.h"

namespace RB
{
	class ObjGroup
	{
	protected:
		std::vector<GameObj*> vecObjs;
		Camera* _camera = nullptr;

	public:
		ColliderData* colliderData = nullptr;
		CollisionData* collisionData = nullptr;
		JumpAdder* jumpAdder = nullptr;
		MessageGetter* messageGetter = nullptr;

		virtual void UpdateStates() = 0;
		virtual void UpdateSpriteTileIndex() = 0;
		virtual void RenderStates() = 0;
		virtual void RenderObjPosition() = 0;
		virtual void RenderBoxColliders() = 0;

		virtual void SetState(int32_t _index, State* newState);
		virtual bool SetNextState(int32_t _index, State* ptrState);
		virtual GameObj* GetObj(int32_t index);
		virtual ObjData* GetObjData(int32_t index);

		virtual void CreateObj(ObjType objType, olc::vi2d startPos) {}
		virtual void DeleteObj(size_t index);

		virtual std::vector<GameObj*>* GetVecObjs();
	};
}