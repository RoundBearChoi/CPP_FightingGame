#include "FightScene.h"

//fighter states
#include "Fighter_0_Idle.h"
#include "Fighter_0_WalkForward.h"
#include "Fighter_0_Jab.h"
#include "Fighter_1_Idle.h"

//background states
#include "Background_Idle_Trees.h"
#include "Background_Idle_Mountains.h"
#include "Background_Idle_Sun.h"

namespace RB
{
	FightScene::FightScene()
	{
		IF_COUT{ std::cout << "constructing FightScene" << std::endl; }
	}

	FightScene::~FightScene()
	{
		IF_COUT{ std::cout << "destructing FightScene" << std::endl; }
	}

	void FightScene::InitScene()
	{
		fighters.SetFighterInfo(0, { -220, 0 });
		fighters.SetFighterInfo(1, { 220, 0 });

		fighters.SetInitialState<Fighter_0_Idle>(0);
		fighters.SetInitialState<Fighter_1_Idle>(1);

		background.SetBackgroundInfo(0, { 0, -250 }); //trees
		background.SetBackgroundInfo(1, { 0, -400 }); //mountains
		background.SetBackgroundInfo(2, { 0, -530 }); //sun

		background.SetInitialState<Background_Idle_Trees>(0);
		background.SetInitialState<Background_Idle_Mountains>(1);
		background.SetInitialState<Background_Idle_Sun>(2);
	}

	void FightScene::Update(GameData& gameData)
	{
		background.UpdateState(gameData);
		background.UpdateOffset(cam);
		fighters.UpdateState(gameData);
	}

	void FightScene::RenderObjs()
	{
		RenderCenterMark(cam);

		background.RenderObjPosition(cam);
		fighters.RenderObjPosition(cam);
	}

	void FightScene::RenderStates(bool update)
	{
		background.RenderStates(ptrDecalLoader, cam, update);
		fighters.RenderStates(ptrDecalLoader, cam, update);
	}
}