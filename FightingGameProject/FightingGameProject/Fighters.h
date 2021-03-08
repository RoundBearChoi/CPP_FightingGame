#pragma once
#include <vector>
#include "GameObj.h"
#include "ObjGroup.h"

namespace RB
{
	class Fighters : public ObjGroup
	{
	private:
		GameObj arrObjs[2];

	public:
		void RenderObjPosition(olc::PixelGameEngine* ptrEngine, olc::vf2d& camPos) override
		{
			for (int i = 0; i < 2; i++)
			{
				arrObjs[i].RenderPosition(ptrEngine, camPos);
			}
		}

		void SetFighterInfo(int _index, olc::vf2d _startingPos)
		{
			size_t count = GetCreationCount();

			arrObjs[_index].objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
			arrObjs[_index].objData.SetCreationID(count);
			arrObjs[_index].objData.SetPosition(_startingPos.x, _startingPos.y);
		}
	};
}