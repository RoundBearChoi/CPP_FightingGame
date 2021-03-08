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
		void RenderObjPosition(olc::PixelGameEngine* ptrEngine, const olc::vi2d& camPos, const float& zoomScale) override
		{
			for (int i = 0; i < 2; i++)
			{
				arrObjs[i].RenderSpriteSize(ptrEngine, camPos, zoomScale);
				arrObjs[i].RenderPosition(ptrEngine, camPos, zoomScale);
			}
		}

		void SetFighterInfo(int _index, olc::vi2d _startingPos)
		{
			size_t count = GetCreationCount();

			arrObjs[_index].objData.SetSpriteSize(180, 180);
			arrObjs[_index].objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
			arrObjs[_index].objData.SetCreationID(count);
			arrObjs[_index].objData.SetPosition(_startingPos.x, _startingPos.y);
		}
	};
}