#include "Fighters.h"
#include "DevSettings.h"

namespace RB
{
	void Fighters::UpdateState(GameData& gameData)
	{
		for (auto i = arrObjs.begin(); i != arrObjs.end(); i++)
		{
			(*i).stateController.MakeStateTransition();

			State* s = (*i).stateController.currentState;

			if (s != nullptr)
			{
				if (s->IsNew())
				{
					s->OnEnter((*i).objData, gameData);
				}
				
				s->UpdateState((*i).objData, gameData);
			}
		}
	}

	void Fighters::RenderObjPosition(Camera& cam)
	{
		for (auto i = arrObjs.begin(); i != arrObjs.end(); i++)
		{
			//(*i).RenderSpriteSize(cam);
			(*i).RenderPosition(cam);
		}
	}

	void Fighters::RenderStates(DecalLoader* ptrDecalLoader, Camera& cam, bool update)
	{
		for (auto i = arrObjs.begin(); i != arrObjs.end(); i++)
		{
			SheetRenderer::Render(ptrDecalLoader, &(*i), cam);

			if (update)
			{
				(*i).stateController.currentState->animationController.UpdateTileIndex();
			}
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