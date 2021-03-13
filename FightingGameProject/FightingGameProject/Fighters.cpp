#include "Fighters.h"
#include "DevSettings.h"

namespace RB
{
	void Fighters::UpdateState(GameData& gameData)
	{
		for (auto i = arrObjs.begin(); i != arrObjs.end(); i++)
		{
			State* s = (*i).stateController.currentState;

			if (s != nullptr)
			{
				s->TriggerEnter((*i).objData, gameData);
				s->UpdateState((*i).objData, gameData);
			}
		}
	}

	void Fighters::RenderObjPosition(olc::PixelGameEngine* ptrEngine, Camera& cam)
	{
		for (auto i = arrObjs.begin(); i != arrObjs.end(); i++)
		{
			(*i).RenderSpriteSize(ptrEngine, cam);
			(*i).RenderPosition(ptrEngine, cam);
		}
	}

	void Fighters::RenderStates(olc::PixelGameEngine* ptrEngine, DecalLoader* ptrDecalLoader, Camera& cam, bool update)
	{
		for (auto i = arrObjs.begin(); i != arrObjs.end(); i++)
		{
			SheetRenderer::Render(ptrEngine, ptrDecalLoader, &(*i), cam, update);
		}
	}

	void Fighters::SetFighterInfo(int32_t _index, olc::vi2d _startingPos)
	{
		size_t count = CreationCount::UpdateCount();

		arrObjs[_index].objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
		arrObjs[_index].objData.SetPosition(_startingPos);

		arrObjs[_index].objData.SetCreationID(count);
		arrObjs[_index].stateController.SetCreationID(count);
	}
}