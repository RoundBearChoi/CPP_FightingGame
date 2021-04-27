#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "ObjType.h"
#include "Camera.h"
#include "BodyType.h"
#include "GameObj.h"

namespace RB
{
	class State;
	class CheckCollisionMessage;
	class SlowMotionMessage;

	class ObjGroup
	{
	protected:
		std::vector<GameObj*> vecObjs;

	public:
		std::vector<SlowMotionMessage> vecSlowMotion;

		virtual void UpdateStates(GameData& gameData) = 0;
		virtual void RenderObjPosition(Camera& cam) = 0;
		virtual void RenderStates(Camera& cam, bool update) = 0;
		virtual bool SetNextState(int32_t _index, State* ptrState) { return false; }
		virtual void RenderBoxColliders(Camera& cam) = 0;

		virtual size_t GetObjCount()
		{
			return vecObjs.size();
		}

		virtual size_t GetObjCreationID(size_t index)
		{
			if (index < vecObjs.size())
			{
				return (vecObjs[index]->objData.GetCreationID());
			}

			return 0;
		}

		virtual olc::vi2d GetObjWorldPos(size_t index) = 0;
		virtual olc::vi2d GetObjBoxColliderWorldPos(size_t index) = 0;
		virtual std::array<olc::vi2d, 4> GetObjBoxColliderWorldQuad(size_t index) = 0;

		virtual olc::vi2d GetBodyWorldPos(int32_t fighterIndex, BodyType bodyType)
		{
			return olc::vi2d(0, 0);
		};

		virtual std::array<olc::vi2d, 4> GetBodyWorldQuad(int32_t fighterIndex, BodyType bodyType)
		{
			std::array<olc::vi2d, 4> arr = { olc::vi2d(0,0), olc::vi2d(0,0), olc::vi2d(0,0), olc::vi2d(0,0) };
			return arr;
		};

		virtual void RenderComponents() {}
		virtual void CreateObj(ObjType objType, olc::vi2d startPos) {}
		virtual void DeleteObj(size_t index) {}
		virtual CheckCollisionMessage* GetCheckCollisionMessage(size_t index) { return nullptr; }
		virtual int32_t GetCollisionCount(int32_t fighterIndex) { return 0; }
		virtual int32_t MaxCollisions(int32_t fighterIndex) { return 0; };
		virtual void AddCollisionCount(int32_t fighterIndex) {}
		virtual void AddJumpProcessor(int32_t index, int32_t upForce, int32_t sideForce) {};

		virtual size_t GetOwnerCreationID(size_t index)
		{ 
			if (index < vecObjs.size())
			{
				if (vecObjs[index] != nullptr)
				{
					return vecObjs[index]->objData.GetOwnerID();
				}
			}

			return 0;
		}
	};
}