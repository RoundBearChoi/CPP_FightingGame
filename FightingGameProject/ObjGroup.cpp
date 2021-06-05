#include "ObjGroup.h"

namespace RB
{
	void ObjGroup::UpdateSpriteTileIndex()
	{
		for (size_t i = 0; i < _vecObjs.size(); i++)
		{
			if (_vecObjs[i] != nullptr)
			{
				_vecObjs[i]->stateController->currentState->animationController.NextTileIndex();
			}
		}
	}

	GameObj* ObjGroup::GetObj(int32_t index)
	{
		if (index >= _vecObjs.size())
		{
			return nullptr;
		}
		else
		{
			return _vecObjs[index];
		}
	}

	ObjData* ObjGroup::GetObjData(int32_t index)
	{
		if (index >= _vecObjs.size())
		{
			return nullptr;
		}
		else
		{
			return &_vecObjs[index]->objData;
		}
	}

	void ObjGroup::DeleteObj(size_t index)
	{
		delete _vecObjs[index];
		_vecObjs[index] = nullptr;
		_vecObjs.erase(_vecObjs.begin() + index);
	}

	std::vector<GameObj*>* ObjGroup::GetVecObjs()
	{
		return &_vecObjs;
	}
}