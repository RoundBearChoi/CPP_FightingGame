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
#include "InputBuffer.h"
#include "InputType.h"
#include "UIElement.h"
#include "CreateProjectile.h"

//combos
#include "Hadouken.h"

//loading
#include "Preload_Fighter_0.h"

namespace RB
{
	class FightersGroup : public ObjGroup
	{
	private:
		std::array<GameObj, 2> arrObjs;
		Preload_Fighter_0 preload_fighter_0;

		UIElement upleft;
		UIElement upright;
		UIElement downleft;
		UIElement downright;

		UIElement left;
		UIElement right;

		UIElement down;

		UIElement punch;

	public:
		FightersGroup();

		void UpdateStates(GameData& gameData) override;
		void RenderObjPosition(Camera& cam) override;
		void RenderStates(Camera& cam, bool update) override;
		void RenderBoxColliders(Camera& cam) override;
		size_t GetObjCount() override;
		olc::vi2d GetObjWorldPos(size_t index) override;
		olc::vi2d GetObjBoxColliderWorldPos(size_t index) override;

		void RenderInputBuffer();
		void SetFighterInfo(int32_t _index, olc::vi2d _startingPos, PlayerType _playerType);
		GameObj* GetEnemyObj(State& me);
		olc::Decal* GetBufferDecal(InputType inputType);
		std::vector<CreateProjectile>* GetProjectileQueues(size_t _index);
		olc::vi2d GetBodyWorldPos(int32_t fighterIndex, BodyType bodyType);

		template<class T>
		void SetInitialState(int32_t _index)
		{
			arrObjs[_index].stateController.CreateNewState<T>();
		}
	};
}