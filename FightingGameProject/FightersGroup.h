#pragma once
#include <vector>
#include <array>
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
		IGroupComponent* _fighterDirection = nullptr;
		IGroupComponent* _fighterJump = nullptr;
		IGroupComponent* _groundToGroundCollision = nullptr;
		IGroupComponent* _specialMoveProcessor = nullptr;
		IGroupComponent* _inputBufferRenderer = nullptr;
		IGroupComponent* _animationRenderer = nullptr;
		Preload_Fighter_0* _preloadFighter0 = nullptr;

		RandomInteger randomInteger;

	public:
		FightersGroup(Camera* camera);
		~FightersGroup();

		void UpdateStates() override;
		void RenderStates(bool update) override;
		void UpdateSpriteTileIndex() override;
		bool SetNextState(int32_t _index, State* ptrState) override;

		void RenderObjPosition() override;
		void RenderBoxColliders() override;
				
		ObjData* GetObjData(int32_t index) override;

		void SetFighterInfo(olc::vi2d _startingPos, PlayerType _playerType);
		GameObj* GetEnemyObj(State& me);
	};
}