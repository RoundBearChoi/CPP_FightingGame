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
		void RenderObjPosition() override
		{
			for (int i = 0; i < 2; i++)
			{
				arrObjs[i].RenderPosition();
			}
		}

		void AddNewFighter(int _index, olc::vf2d pos)
		{
			GameObj newFighter;

			ObjData data;
			data.position = pos;

			newFighter.objData = data;
			newFighter.objData.creationID = GetCreationCount();

			arrObjs[_index] = newFighter;
		}
	};
}