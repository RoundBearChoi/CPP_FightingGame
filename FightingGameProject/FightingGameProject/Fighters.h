#pragma once
#include <vector>
#include <array>
#include "GameObj.h"
#include "ObjGroup.h"
#include "GameData.h"
#include "SheetRenderer.h"
#include "CreationCount.h"

namespace RB
{
	class Fighters : public ObjGroup
	{
	private:
		std::array<GameObj, 2> arrObjs;

	public:
		void SetFighterInfo(int32_t _index, olc::vi2d _startingPos)
		{
			size_t count = CreationCount::UpdateCount();

			arrObjs[_index].objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
			arrObjs[_index].objData.SetPosition(_startingPos);

			arrObjs[_index].objData.SetCreationID(count);
			arrObjs[_index].stateController.SetCreationID(count);
		}

		template<class T>
		void SetInitialState(int32_t _index)
		{
			arrObjs[_index].stateController.CreateNewState<T>();
		}

		void UpdateState(GameData& gameData) override
		{
			for (auto i = arrObjs.begin(); i != arrObjs.end(); i++)
			{
				State* s = (*i).stateController.currentState;

				if (s != nullptr)
				{
					s->Enter((*i).objData, gameData);
					s->UpdateState((*i).objData, gameData);
				}
			}
		}

		void RenderObjPosition(olc::PixelGameEngine* ptrEngine, Camera& cam) override
		{
			for (auto i = arrObjs.begin(); i != arrObjs.end(); i++)
			{
				(*i).RenderSpriteSize(ptrEngine, cam);
				(*i).RenderPosition(ptrEngine, cam);
			}
		}

		void RenderStates(olc::PixelGameEngine* ptrEngine, DecalLoader* ptrDecalLoader, Camera& cam, bool update) override
		{
			for (auto i = arrObjs.begin(); i != arrObjs.end(); i++)
			{
				SheetRenderer::Render(ptrEngine, ptrDecalLoader, &(*i), cam, update);
			}
		}
	};
}