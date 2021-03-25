#include "Fighters.h"

namespace RB
{
	void Fighters::UpdateState(GameData& gameData)
	{
		if (arrObjs[0].objData.GetPosition().x < arrObjs[1].objData.GetPosition().x)
		{
			arrObjs[0].objData.SetLeftSide(true);
		}
		else if (arrObjs[0].objData.GetPosition().x > arrObjs[1].objData.GetPosition().x)
		{
			arrObjs[0].objData.SetLeftSide(false);
		}

		if (arrObjs[1].objData.GetPosition().x < arrObjs[0].objData.GetPosition().x)
		{
			arrObjs[1].objData.SetLeftSide(true);
		}
		else if (arrObjs[1].objData.GetPosition().x > arrObjs[0].objData.GetPosition().x)
		{
			arrObjs[1].objData.SetLeftSide(false);
		}

		for (int32_t i = 0; i < arrObjs.size(); i++)
		{
			arrObjs[i].stateController.MakeStateTransition();

			if (arrObjs[i].objData.IsOnLeftSide())
			{
				arrObjs[i].objData.FaceRight(true);
			}
			else
			{
				arrObjs[i].objData.FaceRight(false);
			}

			State* s = arrObjs[i].stateController.currentState;

			if (s != nullptr)
			{
				if (s->IsNew())
				{
					s->OnEnter(arrObjs[i].objData, gameData);
				}

				//update every single frame
				s->UpdateState(arrObjs[i].objData, gameData);

				//update on every animation update (delay applied)
				if (arrObjs[i].stateController.currentState->animationController.status.nDelayCount == 0)
				{
					s->OnAnimationUpdate(arrObjs[i].objData, gameData);
				}

				if (s->DoCollisionCheck())
				{
					IF_COUT{ std::cout << "fighter creation id: " << arrObjs[i].objData.GetCreationID() << std::endl; }
				}
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
				arrObjs[i].stateController.currentState->animationController.NextTileIndex();
			}
		}
	}

	void Fighters::RenderBoxColliders(Camera& cam)
	{
		for (int32_t i = 0; i < arrObjs.size(); i++)
		{
			arrObjs[i].stateController.currentState->RenderColliderQuads(arrObjs[i].objData, cam);
		}
	}

	void Fighters::SetFighterInfo(int32_t _index, olc::vi2d _startingPos, PlayerType _playerType)
	{
		size_t count = CreationCount::UpdateCount();

		arrObjs[_index].objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
		arrObjs[_index].objData.SetPosition(_startingPos);

		arrObjs[_index].objData.SetCreationID(count);
		arrObjs[_index].stateController.SetCreationID(count);

		arrObjs[_index].objData.SetPlayerType(_playerType);
	}
}