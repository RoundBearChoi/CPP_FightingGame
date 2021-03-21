#pragma once
#include <array>
#include "ObjGroup.h"
#include "GameObj.h"
#include "SheetRenderer.h"
#include "CreationCount.h"

namespace RB
{
	class Background : public ObjGroup
	{
	private:
		std::array<GameObj, 3> arrObjs;

	public:
		void UpdateState(GameData& gameData) override;
		void RenderObjPosition(Camera& cam) override;
		void RenderStates(Camera& cam, bool update) override;

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