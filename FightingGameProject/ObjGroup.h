#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "ObjType.h"
#include "GameObj.h"

namespace RB
{
	class ObjGroup
	{
	protected:
		std::vector<GameObj*> vecObjs;

	public:
		std::vector<SlowMotionMessage> vecSlowMotion;

		virtual void UpdateStates(GameData& gameData) = 0;
		virtual void RenderStates(Camera& cam, bool update) = 0;
		virtual bool SetNextState(int32_t _index, State* ptrState) { return false; }

		virtual void RenderObjPosition(Camera& cam) = 0;
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

		virtual olc::vi2d GetObjWorldPos(size_t index)
		{
			if (index < vecObjs.size())
			{
				return vecObjs[index]->objData.GetPosition();
			}

			return olc::vi2d(0, 0);
		}

		virtual olc::vi2d GetObjBoxColliderWorldPos(size_t index)
		{
			if (index < vecObjs.size())
			{
				if (vecObjs[index] != nullptr)
				{
					olc::vi2d relativePos = vecObjs[index]->objData.objBoxCollider.RelativePosition();
					olc::vi2d worldPos = relativePos + vecObjs[index]->objData.GetPosition();
					return worldPos;
				}
			}

			return olc::vi2d(0, 0);
		}

		virtual std::array<olc::vi2d, 4> GetObjBoxColliderWorldQuad(size_t index)
		{
			std::array<olc::vi2d, 4> arr;

			if (index < vecObjs.size())
			{
				if (vecObjs[index] != nullptr)
				{
					arr[0] = vecObjs[index]->objData.objBoxCollider.RelativePoint0();
					arr[1] = vecObjs[index]->objData.objBoxCollider.RelativePoint1();
					arr[2] = vecObjs[index]->objData.objBoxCollider.RelativePoint2();
					arr[3] = vecObjs[index]->objData.objBoxCollider.RelativePoint3();

					olc::vi2d relativePos = vecObjs[index]->objData.objBoxCollider.RelativePosition();

					arr[0] += relativePos;
					arr[1] += relativePos;
					arr[2] += relativePos;
					arr[3] += relativePos;

					olc::vi2d playerPos = vecObjs[index]->objData.GetPosition();

					arr[0] += playerPos;
					arr[1] += playerPos;
					arr[2] += playerPos;
					arr[3] += playerPos;
				}
			}

			return arr;
		}

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

		virtual void DeleteObj(size_t index)
		{
			delete vecObjs[index];
			vecObjs[index] = nullptr;
			vecObjs.erase(vecObjs.begin() + index);
		}

		virtual CheckCollisionMessage* GetCheckCollisionMessage(size_t index)
		{
			if (index < vecObjs.size())
			{
				if (vecObjs[index]->stateController.currentState != nullptr)
				{
					if (vecObjs[index]->stateController.currentState->vecCheckCollisions.size() > 0)
					{
						return vecObjs[index]->stateController.currentState->GetCollisionStatus();
					}
				}
			}

			return nullptr;
		}

		virtual int32_t GetCollisionCount(int32_t fighterIndex)
		{
			if (fighterIndex < vecObjs.size())
			{
				if (vecObjs[fighterIndex]->stateController.currentState != nullptr)
				{
					return vecObjs[fighterIndex]->stateController.currentState->bodyCollisionCount;
				}
			}

			return 0;
		}

		virtual int32_t GetMaxCollisions(int32_t fighterIndex)
		{
			if (fighterIndex < vecObjs.size())
			{
				if (vecObjs[fighterIndex]->stateController.currentState != nullptr)
				{
					return vecObjs[fighterIndex]->stateController.currentState->maxBodyCollisions;
				}
			}

			return 0;
		};

		virtual void AddCollisionCount(int32_t fighterIndex)
		{
			vecObjs[fighterIndex]->stateController.currentState->bodyCollisionCount++;
		}

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