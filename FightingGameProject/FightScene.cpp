#include "FightScene.h"

namespace RB
{
	FightScene::FightScene()
	{
		IF_COUT{ std::cout << "constructing FightScene" << std::endl; };
	}

	FightScene::~FightScene()
	{
		IF_COUT{ std::cout << "destructing FightScene" << std::endl; };
	}

	void FightScene::InitScene()
	{
		fighters.SetFighterInfo(0, { -100, 0 }, PlayerType::PLAYER_1);
		fighters.SetFighterInfo(1, { 100, 0 }, PlayerType::PLAYER_2);

		fighters.SetInitialState<Fighter_0_Idle>(0);
		fighters.SetInitialState<Fighter_0_Idle>(1);

		background.SetBackgroundInfo(0, { 0, -250 }); //trees
		background.SetBackgroundInfo(1, { 0, -400 }); //mountains
		background.SetBackgroundInfo(2, { 0, -530 }); //sun

		background.SetInitialState<Background_Idle_Trees>(0);
		background.SetInitialState<Background_Idle_Mountains>(1);
		background.SetInitialState<Background_Idle_Sun>(2);
	}

	void FightScene::Update(GameData& gameData)
	{
		//update objs
		background.UpdateStates(gameData);
		background.UpdateOffset(cam);
		fighters.UpdateStates(gameData);

		//create projectiles
		std::vector<CreateProjectile>* p1 = fighters.GetProjectileQueues(0);
		std::vector<CreateProjectile>* p2 = fighters.GetProjectileQueues(1);

		projectiles.CreateProjectiles(*p1);
		projectiles.CreateProjectiles(*p2);

		p1->clear();
		p2->clear();

		//update objs
		projectiles.UpdateStates(gameData);
	}

	void FightScene::RenderObjs()
	{
		RenderCenterMark(cam);

		background.RenderObjPosition(cam);

		fighters.RenderObjPosition(cam);
		fighters.RenderInputBuffer();

		projectiles.RenderObjPosition(cam);

		//testing collision between projectiles vs players
		//player1
		//olc::vi2d f1Pos = fighters.GetObjWorldPos(0);
		//olc::vi2d f1ColPos = fighters.GetBodyWorldPos(0, BodyType::HEAD);
		size_t fighterID = fighters.GetObjCreationID(0);

		//player2
		olc::vi2d f2Pos = fighters.GetObjWorldPos(1);
		olc::vi2d f2ColPos = fighters.GetBodyWorldPos(1, BodyType::HEAD);

		//body collider render test
		olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(f2ColPos, cam), olc::CYAN);

		std::array<olc::vi2d, 4>bodyQuads = fighters.GetBodyWorldQuad(1, BodyType::HEAD);
		olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(bodyQuads[0], cam), olc::CYAN);
		olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(bodyQuads[1], cam), olc::CYAN);
		olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(bodyQuads[2], cam), olc::CYAN);
		olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(bodyQuads[3], cam), olc::CYAN);

		size_t count = projectiles.GetObjCount();

		for (size_t i = 0; i < count; i++)
		{
			size_t ownerID = projectiles.GetObjCreationID(i);

			olc::vi2d worldPos = projectiles.GetObjBoxColliderWorldPos(i);
			olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(worldPos, cam), olc::CYAN);

			std::array<olc::vi2d, 4>projectileQuads = projectiles.GetObjBoxColliderWorldQuad(i);
			olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(projectileQuads[0], cam), olc::CYAN);
			olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(projectileQuads[1], cam), olc::CYAN);
			olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(projectileQuads[2], cam), olc::CYAN);
			olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(projectileQuads[3], cam), olc::CYAN);

			//DiagonalOverlap::yes()
		}
	}

	void FightScene::RenderStates(bool update)
	{
		background.RenderStates(cam, update);
		fighters.RenderStates(cam, update);
		fighters.RenderBoxColliders(cam);
		projectiles.RenderStates(cam, update);
	}
}