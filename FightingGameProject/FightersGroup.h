#pragma once
#include <vector>
#include <array>
#include "GameObj.h"
#include "GameData.h"
#include "ObjGroup.h"

//components
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
		std::array<GameObj, 2> arrObjs;

		GroupComponent* ptrFighterJump = nullptr;
		GroupComponent* ptrGroundToGroundCollision = nullptr;
		GroupComponent* ptrSpecialMoveProcessor = nullptr;
		GroupComponent* ptrInputBufferRenderer = nullptr;
		GroupComponent* ptrAnimationRenderer = nullptr;

		Preload_Fighter_0 preload_fighter_0;
		RandomInteger randomInteger;

	public:
		FightersGroup();
		~FightersGroup();

		void UpdateStates(GameData& gameData) override;
		void RenderObjPosition(Camera& cam) override;
		void RenderStates(Camera& cam, bool update) override;
		bool SetNextState(int32_t _index, State* ptrState) override;
		void RenderBoxColliders(Camera& cam) override;
		
		size_t GetObjCount() override;
		size_t GetObjCreationID(size_t index) override;
		olc::vi2d GetObjWorldPos(size_t index) override;
		olc::vi2d GetObjBoxColliderWorldPos(size_t index) override;
		std::array<olc::vi2d, 4> GetObjBoxColliderWorldQuad(size_t index) override;
		olc::vi2d GetBodyWorldPos(int32_t fighterIndex, BodyType bodyType) override;
		std::array<olc::vi2d, 4> GetBodyWorldQuad(int32_t fighterIndex, BodyType bodyType) override;
		void RenderComponents() override;
		CheckCollisionMessage* GetCollisionQueue(size_t index) override;
		int32_t GetCollisionCount(int32_t fighterIndex) override;
		int32_t MaxCollisions(int32_t fighterIndex) override;
		void AddCollisionCount(int32_t fighterIndex) override;
		void AddJumpProcessor(int32_t index, int32_t upForce, int32_t sideForce) override;

		void SetFighterInfo(int32_t _index, olc::vi2d _startingPos, PlayerType _playerType);
		GameObj* GetEnemyObj(State& me);
		std::vector<CreateProjectileMessage>* GetProjectileQueues(size_t _index);
		
		template<class T>
		void SetInitialState(int32_t _index)
		{
			arrObjs[_index].stateController.CreateNewState<T>();
		}
	};
}