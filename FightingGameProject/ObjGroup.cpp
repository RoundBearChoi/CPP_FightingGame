#include "ObjGroup.h"

namespace RB
{
	void ObjGroup::SetState(int32_t _index, State* newState)
	{
		if (newState != nullptr)
		{
			if (vecObjs[_index]->stateController->currentState != nullptr)
			{
				delete vecObjs[_index]->stateController->currentState;
			}

			vecObjs[_index]->stateController->currentState = newState;
		}
	}

	bool ObjGroup::SetNextState(int32_t _index, State* ptrState)
	{
		return false;
	}

	GameObj* ObjGroup::GetObj(int32_t index)
	{
		if (index >= vecObjs.size())
		{
			return nullptr;
		}
		else
		{
			return vecObjs[index];
		}
	}

	ObjData* ObjGroup::GetObjData(int32_t index)
	{
		if (index >= vecObjs.size())
		{
			return nullptr;
		}
		else
		{
			return &vecObjs[index]->objData;
		}
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

	std::vector<GameObj*>* ObjGroup::GetVecObjs()
	{
		return &vecObjs;
	}
}