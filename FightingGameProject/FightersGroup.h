#pragma once
#include <vector>
#include <array>
#include "GameObj.h"
#include "ObjGroup.h"
#include "GameData.h"
#include "CreationCount.h"
#include "DevSettings.h"
#include "PlayerType.h"
#include "InputBuffer.h"
#include "InputType.h"
#include "UIElement.h"
#include "CreateProjectile.h"
#include "SheetRenderer.h"
#include "BodyCollision.h"

//combos
#include "ComboChecker.h"
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
		size_t GetObjCreationID(size_t index) override;
		olc::vi2d GetObjWorldPos(size_t index) override;
		olc::vi2d GetObjBoxColliderWorldPos(size_t index) override;
		std::array<olc::vi2d, 4> GetObjBoxColliderWorldQuad(size_t index) override;

		void RenderInputBuffer(olc::vi2d& startPos, std::vector<InputElement>& vecInputs);
		void SetFighterInfo(int32_t _index, olc::vi2d _startingPos, PlayerType _playerType);
		GameObj* GetEnemyObj(State& me);
		olc::Decal* GetBufferDecal(InputType inputType);
		std::vector<CreateProjectile>* GetProjectileQueues(size_t _index);
		olc::vi2d GetBodyWorldPos(int32_t fighterIndex, BodyType bodyType);
		std::array<olc::vi2d, 4> GetBodyWorldQuad(int32_t fighterIndex, BodyType bodyType);

		template<class T>
		void SetInitialState(int32_t _index)
		{
			arrObjs[_index].stateController.CreateNewState<T>();
		}

		template<class T>
		void MakeNewState(int32_t _index)
		{
			if (_index < arrObjs.size())
			{
				if (arrObjs[_index].stateController.currentState != nullptr)
				{
					arrObjs[_index].stateController.currentState->nextState = State::NewState<T>();
				}
			}
		}
	};
}