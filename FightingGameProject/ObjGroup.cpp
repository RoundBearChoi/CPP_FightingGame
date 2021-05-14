#include "ObjGroup.h"

namespace RB
{
	bool ObjGroup::SetNextState(int32_t _index, State* ptrState)
	{
		return false;
	}

	size_t ObjGroup::GetObjCount()
	{
		return vecObjs.size();
	}

	size_t ObjGroup::GetObjCreationID(size_t index)
	{
		if (index < vecObjs.size())
		{
			return (vecObjs[index]->objData.GetCreationID());
		}

		return 0;
	}

	size_t ObjGroup::GetOwnerCreationID(size_t index)
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

	olc::vi2d ObjGroup::GetObjWorldPos(size_t index)
	{
		if (index < vecObjs.size())
		{
			return vecObjs[index]->objData.GetPosition();
		}

		return olc::vi2d(0, 0);
	}

	olc::vi2d ObjGroup::GetObjBoxColliderWorldPos(size_t index)
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

	std::array<olc::vi2d, 4> ObjGroup::GetObjBoxColliderWorldQuad(size_t index)
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

	olc::vi2d ObjGroup::GetBodyWorldPos(int32_t fighterIndex, BodyType bodyType)
	{
		return olc::vi2d(0, 0);
	};

	std::array<olc::vi2d, 4> ObjGroup::GetBodyWorldQuad(int32_t fighterIndex, BodyType bodyType)
	{
		std::array<olc::vi2d, 4> arr = { olc::vi2d(0,0), olc::vi2d(0,0), olc::vi2d(0,0), olc::vi2d(0,0) };
		return arr;
	};

	void ObjGroup::DeleteObj(size_t index)
	{
		delete vecObjs[index];
		vecObjs[index] = nullptr;
		vecObjs.erase(vecObjs.begin() + index);
	}

	CheckCollisionMessage* ObjGroup::GetCheckCollisionMessage(size_t index)
	{
		if (index < vecObjs.size())
		{
			if (vecObjs[index]->stateController->currentState != nullptr)
			{
				if (vecObjs[index]->stateController->currentState->vecCheckCollisions.size() > 0)
				{
					return vecObjs[index]->stateController->currentState->GetCollisionStatus();
				}
			}
		}

		return nullptr;
	}

	int32_t ObjGroup::GetCollisionCount(int32_t fighterIndex)
	{
		if (fighterIndex < vecObjs.size())
		{
			if (vecObjs[fighterIndex]->stateController->currentState != nullptr)
			{
				return vecObjs[fighterIndex]->stateController->currentState->bodyCollisionCount;
			}
		}

		return 0;
	}

	int32_t ObjGroup::GetMaxCollisions(int32_t fighterIndex)
	{
		if (fighterIndex < vecObjs.size())
		{
			if (vecObjs[fighterIndex]->stateController->currentState != nullptr)
			{
				return vecObjs[fighterIndex]->stateController->currentState->maxBodyCollisions;
			}
		}

		return 0;
	};

	void ObjGroup::AddCollisionCount(int32_t fighterIndex)
	{
		vecObjs[fighterIndex]->stateController->currentState->bodyCollisionCount++;
	}

	std::vector<CreateProjectileMessage>* ObjGroup::GetProjectileQueues(size_t _index)
	{
		if (_index < vecObjs.size())
		{
			return &vecObjs[_index]->stateController->currentState->vecCreateProjectiles;
		}

		return nullptr;
	}
}