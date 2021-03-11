#pragma once
#include "ObjGroup.h"
#include "GameObj.h"
#include "SheetRenderer.h"
#include "CreationCount.h"

namespace RB
{
	class Background : public ObjGroup
	{
	private:
		GameObj arrObjs[2];

	public:
		void SetBackgroundInfo(int32_t _index, olc::vi2d _startingPos)
		{
			size_t count = CreationCount::UpdateCount();

			arrObjs[_index].objData.SetSpriteSize({ 854, 480 });
			arrObjs[_index].objData.SetOffsetType(OffsetType::CENTER_CENTER);
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
			for (int32_t i = 0; i < 2; i++)
			{
				State* s = arrObjs[i].stateController.currentState;

				if (s != nullptr)
				{
					s->Enter(arrObjs[i].objData, gameData);
					s->UpdateState(arrObjs[i].objData, gameData);
				}
			}
		}

		void RenderObjPosition(olc::PixelGameEngine* ptrEngine, Camera& cam) override
		{
			for (int32_t i = 0; i < 2; i++)
			{
				arrObjs[i].RenderSpriteSize(ptrEngine, cam);
				arrObjs[i].RenderPosition(ptrEngine, cam);
			}
		}

		void RenderStates(olc::PixelGameEngine* ptrEngine, DecalLoader* ptrDecalLoader, Camera& cam, bool update) override
		{
			for (int32_t i = 0; i < 2; i++)
			{
				SheetRenderer::Render(ptrEngine, ptrDecalLoader, &arrObjs[i], cam, update);
			}
		}
	};
}