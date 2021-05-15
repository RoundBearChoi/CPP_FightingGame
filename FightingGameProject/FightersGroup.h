#pragma once
#include <vector>
#include <array>
#include "GameData.h"
#include "ObjGroup.h"

//components
#include "FighterDirection.h"
#include "FighterJump.h"
#include "FighterGroundToGroundCollision.h"
#include "SpecialMoveProcessor.h"
#include "InputBufferRenderer.h"
#include "AnimationRenderer.h"

//loading (temp)
#include "Preload_Fighter_0.h"

namespace RB
{
	class FightersGroup : public ObjGroup
	{
	private:
		GroupComponent* ptrFighterDirection = nullptr;
		GroupComponent* ptrFighterJump = nullptr;
		GroupComponent* ptrGroundToGroundCollision = nullptr;
		GroupComponent* ptrSpecialMoveProcessor = nullptr;
		GroupComponent* ptrInputBufferRenderer = nullptr;
		GroupComponent* ptrAnimationRenderer = nullptr;
		Preload_Fighter_0* preload_fighter_0 = nullptr;

		RandomInteger randomInteger;

	public:
		FightersGroup(GameDataFactory* gameDataFactory);
		~FightersGroup();

		void UpdateStates() override;
		void RenderStates(Camera& cam, bool update) override;
		bool SetNextState(int32_t _index, State* ptrState) override;

		void RenderObjPosition(Camera& cam) override;
		void RenderBoxColliders(Camera& cam) override;

		olc::vi2d GetBodyWorldPos(int32_t fighterIndex, BodyType bodyType) override;
		std::array<olc::vi2d, 4> GetBodyWorldQuad(int32_t fighterIndex, BodyType bodyType) override;

		void AddJumpProcessor(int32_t index, int32_t upForce, int32_t sideForce) override;
		void RenderComponents() override;
		
		void SetFighterInfo(olc::vi2d _startingPos, PlayerType _playerType);
		GameObj* GetEnemyObj(State& me);
		
		void SetState(int32_t _index, State* newState)
		{
			if (newState != nullptr)
			{
				if (vecObjs[_index]->stateController->currentState != nullptr)
				{
					delete vecObjs[_index]->stateController->currentState;
				}

				vecObjs[_index]->stateController->currentState = newState;
			}
		}

		ObjData* GetObjData(int32_t index) override;
	};
}