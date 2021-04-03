#include "BackgroundGroup.h"

namespace RB
{
	void BackgroundGroup::UpdateStates(GameData& gameData)
	{
		for (int32_t i = 0; i < arrObjs.size(); i++)
		{
			State* state = arrObjs[i].stateController.currentState;

			if (state != nullptr)
			{
				state->RunUpdateProcess(arrObjs[i].objData, gameData);
			}
		}
	}

	void BackgroundGroup::RenderObjPosition(Camera& cam)
	{
		//arrObjs[0].RenderSpriteSize(cam);
		arrObjs[1].RenderPosition(cam);
		arrObjs[2].RenderPosition(cam);
	}

	void BackgroundGroup::RenderStates(Camera& cam, bool update)
	{
		SheetRenderer::Render(&arrObjs[2], cam);
		SheetRenderer::Render(&arrObjs[1], cam);
		SheetRenderer::Render(&arrObjs[0], cam);
	}

	void BackgroundGroup::RenderBoxColliders(Camera& cam)
	{
		//do nothing
	}

	void BackgroundGroup::SetBackgroundInfo(int32_t _index, olc::vi2d _startingPos)
	{
		size_t count = CreationCount::UpdateCount();

		arrObjs[_index].objData.SetOffsetType(OffsetType::CENTER_CENTER);
		arrObjs[_index].objData.SetPosition(_startingPos);
		arrObjs[_index].objData.SetCreationID(count);
	}

	void BackgroundGroup::SetBackgroundPosition(int32_t _index, olc::vi2d _pos)
	{
		arrObjs[_index].objData.SetPosition(_pos);
	}

	void BackgroundGroup::UpdateOffset(Camera& cam)
	{
		float x0 = (float)cam.GetPosition().x * 0.65f;
		float x1 = (float)cam.GetPosition().x * 0.8f;
		float x2 = (float)cam.GetPosition().x * 0.9f;

		olc::vi2d pos0{ (int32_t)std::round(x0), arrObjs[0].objData.GetPosition().y };
		olc::vi2d pos1{ (int32_t)std::round(x1), arrObjs[1].objData.GetPosition().y };
		olc::vi2d pos2{ (int32_t)std::round(x2), arrObjs[2].objData.GetPosition().y };

		arrObjs[0].objData.SetPosition(pos0);
		arrObjs[1].objData.SetPosition(pos1);

		float sunX = 350.0f / cam.GetZoom();
		pos2.x += (int32_t)std::round(sunX);
		arrObjs[2].objData.SetPosition(pos2);
	}
}