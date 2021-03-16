#include "Background.h"

namespace RB
{
	void Background::UpdateState(GameData& gameData)
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

	void Background::RenderObjPosition(Camera& cam)
	{
		//arrObjs[0].RenderSpriteSize(cam);
		arrObjs[1].RenderPosition(cam);
		arrObjs[2].RenderPosition(cam);
	}

	void Background::RenderStates(DecalLoader* ptrDecalLoader, Camera& cam, bool update)
	{
		SheetRenderer::Render(ptrDecalLoader, &arrObjs[2], cam, update);
		SheetRenderer::Render(ptrDecalLoader, &arrObjs[1], cam, update);
		SheetRenderer::Render(ptrDecalLoader, &arrObjs[0], cam, update);
	}

	void Background::SetBackgroundInfo(int32_t _index, olc::vi2d _startingPos)
	{
		size_t count = CreationCount::UpdateCount();

		arrObjs[_index].objData.SetOffsetType(OffsetType::CENTER_CENTER);
		arrObjs[_index].objData.SetPosition(_startingPos);

		arrObjs[_index].objData.SetCreationID(count);
		arrObjs[_index].stateController.SetCreationID(count);
	}

	void Background::SetBackgroundPosition(int32_t _index, olc::vi2d _pos)
	{
		arrObjs[_index].objData.SetPosition(_pos);
	}

	void Background::UpdateOffset(Camera& cam)
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