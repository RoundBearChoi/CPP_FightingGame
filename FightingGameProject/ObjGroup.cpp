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