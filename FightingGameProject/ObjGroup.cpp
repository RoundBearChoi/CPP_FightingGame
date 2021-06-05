#include "ObjGroup.h"

namespace RB
{
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