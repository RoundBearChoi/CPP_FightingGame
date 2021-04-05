#pragma once
#include <array>
#include "ObjGroup.h"
#include "GameObj.h"
#include "CreationCount.h"
#include "SheetRenderer.h"

namespace RB
{
	class BackgroundGroup : public ObjGroup
	{
	private:
		std::array<GameObj, 3> arrObjs;

	public:
		void UpdateStates(GameData& gameData) override;
		void RenderObjPosition(Camera& cam) override;
		void RenderStates(Camera& cam, bool update) override;
		void RenderBoxColliders(Camera& cam) override;
		size_t GetObjCount() override;
		olc::vi2d GetObjBoxColliderWorldPos(size_t index) override;

		void SetBackgroundInfo(int32_t _index, olc::vi2d _startingPos);
		void SetBackgroundPosition(int32_t _index, olc::vi2d _pos);
		void UpdateOffset(Camera& cam);

		template<class T>
		void SetInitialState(int32_t _index)
		{
			arrObjs[_index].stateController.CreateNewState<T>();
		}
	};
}