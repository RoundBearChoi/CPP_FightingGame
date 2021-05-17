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

	void ObjGroup::DeleteObj(size_t index)
	{
		delete vecObjs[index];
		vecObjs[index] = nullptr;
		vecObjs.erase(vecObjs.begin() + index);
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