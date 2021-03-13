#pragma once
#include <vector>
#include <array>
#include "GameObj.h"
#include "ObjGroup.h"
#include "GameData.h"
#include "SheetRenderer.h"
#include "CreationCount.h"

namespace RB
{
	class Fighters : public ObjGroup
	{
	private:
		std::array<GameObj, 2> arrObjs;

	public:
		void UpdateState(GameData& gameData) override;
		void RenderObjPosition(olc::PixelGameEngine* ptrEngine, Camera& cam) override;
		void RenderStates(olc::PixelGameEngine* ptrEngine, DecalLoader* ptrDecalLoader, Camera& cam, bool update) override;

		void SetFighterInfo(int32_t _index, olc::vi2d _startingPos);

		template<class T>
		void SetInitialState(int32_t _index)
		{
			arrObjs[_index].stateController.CreateNewState<T>();
		}
	};
}