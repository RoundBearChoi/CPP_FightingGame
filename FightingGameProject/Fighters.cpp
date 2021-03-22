#include "Fighters.h"
#include "DevSettings.h"

namespace RB
{
	void Fighters::UpdateState(GameData& gameData)
	{
		for (int32_t i = 0; i < arrObjs.size(); i++)
		{
			arrObjs[i].stateController.MakeStateTransition();

			State* s = arrObjs[i].stateController.currentState;

			if (s != nullptr)
			{
				if (s->IsNew())
				{
					s->OnEnter(arrObjs[i].objData, gameData);
				}

				s->UpdateState(arrObjs[i].objData, gameData);
			}
		}
	}

	void Fighters::RenderObjPosition(Camera& cam)
	{
		for (int32_t i = 0; i < arrObjs.size(); i++)
		{
			//arrObjs[i].RenderSpriteSize(cam);
			arrObjs[i].RenderPosition(cam);
		}
	}

	void Fighters::RenderStates(Camera& cam, bool update)
	{
		for (int32_t i = 0; i < arrObjs.size(); i++)
		{
			SheetRenderer::Render(&arrObjs[i], cam);

			if (update)
			{
				arrObjs[i].stateController.currentState->animationController.UpdateTileIndex();
			}
		}
	}

	void Fighters::RenderBoxColliders(Camera& cam)
	{
		for (int32_t i = 0; i < arrObjs.size(); i++)
		{
			arrObjs[i].stateController.currentState->RenderBoxColliders(arrObjs[i].objData, cam);
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