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

			arrObjs[_index].objData.SetOffsetType(OffsetType::CENTER_CENTER);
			arrObjs[_index].objData.SetPosition(_startingPos);

			arrObjs[_index].objData.SetCreationID(count);
			arrObjs[_index].stateController.SetCreationID(count);
		}

		void SetBackgroundPosition(int32_t _index, olc::vi2d _pos)
		{
			arrObjs[_index].objData.SetPosition(_pos);
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

		void UpdateOffset(Camera& cam)
		{
			float x0 = (float)cam.GetPosition().x * 0.65f;
			float x1 = (float)cam.GetPosition().x * 0.8f;

			olc::vi2d pos0{ (int32_t)std::round(x0), arrObjs[0].objData.GetPosition().y };
			olc::vi2d pos1{ (int32_t)std::round(x1), arrObjs[1].objData.GetPosition().y };

			arrObjs[0].objData.SetPosition(pos0);
			arrObjs[1].objData.SetPosition(pos1);
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