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
		void RenderObjPosition(olc::PixelGameEngine* ptrEngine) override
		{
			for (int i = 0; i < 2; i++)
			{
				arrObjs[i].RenderPosition(ptrEngine);
			}
		}

		void SetFighterInfo(int _index, olc::vf2d _startingPos)
		{
			arrObjs[_index].objData.creationID = GetCreationCount();
			arrObjs[_index].objData.position = _startingPos;
		}
	};
}