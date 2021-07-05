#pragma once
#include <vector>
#include <array>
#include "ObjGroup.h"
#include "FightersFixedUpdater.h"
#include "FightersHitStopMessage.h"

//update components
#include "FighterDirection.h"
#include "FighterJump.h"
#include "FighterGroundToGroundCollision.h"
#include "SpecialMoveProcessor.h"
#include "InputBufferRenderer.h"

//render components
#include "AnimationRenderer.h"
#include "PreviousPositionRenderer.h"

//loading (temp)
#include "Preload_Fighter_0.h"

namespace RB
{
	class FightersGroup : public ObjGroup
	{
	private:
		std::vector<IGroupComponent*> _vecUpdateComponents;
		std::vector<IGroupComponent*> _vecRenderComponents;

		IGroupComponent* _inputBufferRenderer = nullptr;
		
		Preload_Fighter_0* _preloadFighter0 = nullptr;

		RandomInteger randomInteger;
		
	public:
		FightersGroup(Camera* camera);
		~FightersGroup();

		void UpdateStates() override;
		void RenderStates() override;
		void UpdateSpriteTileIndex() override;

		void RenderObjPosition() override;
		void RenderBoxColliders() override;

		void CreateFighterObj(olc::vi2d _startingPos, PlayerType _playerType);
	};
}