#pragma once
#include <vector>
#include "GameObj.h"
#include "ObjGroup.h"
#include "GameData.h"

namespace RB
{
	class Fighters : public ObjGroup
	{
	private:
		GameObj arrObjs[2];

	public:
		void SetFighterInfo(int _index, olc::vi2d _startingPos)
		{
			size_t count = GetCreationCount();

			arrObjs[_index].objData.SetSpriteSize({ 180, 180 });
			arrObjs[_index].objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
			arrObjs[_index].objData.SetPosition(_startingPos);

			arrObjs[_index].objData.SetCreationID(count);
			arrObjs[_index].stateController.SetCreationID(count);
		}

		template<class T>
		void SetInitialState(int _index)
		{
			arrObjs[_index].stateController.CreateNewState<T>();
		}

		void UpdateState(GameData& gameData)
		{
			for (int i = 0; i < 2; i++)
			{
				State* s = arrObjs[i].stateController.currentState;
				
				if (s != nullptr)
				{
					s->Enter(arrObjs[i].objData, gameData);
					s->UpdateState(arrObjs[i].objData, gameData);
				}
			}
		}

		void RenderObjPosition(olc::PixelGameEngine* ptrEngine, const olc::vi2d& camPos, const float& zoomScale) override
		{
			for (int i = 0; i < 2; i++)
			{
				arrObjs[i].RenderSpriteSize(ptrEngine, camPos, zoomScale);
				arrObjs[i].RenderPosition(ptrEngine, camPos, zoomScale);
			}
		}

		void RenderStates(olc::PixelGameEngine* ptrEngine, DecalLoader* ptrDecalLoader, const olc::vi2d& camPos, const float& zoomScale) override
		{

		}
	};
}