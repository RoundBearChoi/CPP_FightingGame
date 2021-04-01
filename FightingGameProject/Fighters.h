#pragma once
#include <vector>
#include <array>
#include "GameObj.h"
#include "ObjGroup.h"
#include "GameData.h"
#include "SheetRenderer.h"
#include "CreationCount.h"
#include "DevSettings.h"
#include "PlayerType.h"
#include "DiagonalOverlap.h"
#include "InputQueue.h"

//for loading
#include "Preload_Fighter_0.h"

namespace RB
{
	class Fighters : public ObjGroup
	{
	private:
		std::array<GameObj, 2> arrObjs;
		Preload_Fighter_0 preload_fighter_0;

	public:
		void UpdateState(GameData& gameData) override;
		void RenderObjPosition(Camera& cam) override;
		void RenderStates(Camera& cam, bool update) override;
		void RenderBoxColliders(Camera& cam) override;

		void SetFighterInfo(int32_t _index, olc::vi2d _startingPos, PlayerType _playerType);
		State* GetEnemyState(State& me);
		GameObj* GetEnemyObj(State& me);

		template<class T>
		void SetInitialState(int32_t _index)
		{
			arrObjs[_index].stateController.CreateNewState<T>();
		}
	};
}