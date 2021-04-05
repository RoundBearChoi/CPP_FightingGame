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
		//projectile collision
		for (size_t projectileIndex = 0; projectileIndex < projectiles.GetObjCount(); projectileIndex++)
		{
			for (int32_t playerIndex = 0; playerIndex < 2; playerIndex++)
			{
				size_t id = fighters.GetObjCreationID(playerIndex);
				size_t ownerID = projectiles.GetObjCreationID(projectileIndex);

				if (id != ownerID)
				{
					olc::vi2d projectilePos = projectiles.GetObjBoxColliderWorldPos(projectileIndex);

					for (int32_t bodyIndex = 0; bodyIndex <= (int32_t)BodyType::RIGHT_FOOT; bodyIndex++)
					{
						olc::vi2d bodyPos = fighters.GetBodyWorldPos(playerIndex, (BodyType)bodyIndex);

						std::array<olc::vi2d, 4>projectileQuads = projectiles.GetObjBoxColliderWorldQuad(projectileIndex);
						std::array<olc::vi2d, 4>bodyQuads = fighters.GetBodyWorldQuad(playerIndex, (BodyType)bodyIndex);

						//collision test
						if (DiagonalOverlap::yes(projectilePos, projectileQuads, bodyPos, bodyQuads))
						{
							IF_COUT{ std::cout << "projectile collision against player: " << playerIndex << std::endl; };
							IF_COUT{ std::cout << "projectile collision against body: " << bodyIndex << std::endl; };
						}
					}
				}
			}
		}

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

		//update projectiles
		projectiles.UpdateStates(gameData);
	}

	void FightScene::RenderObjs()
	{
		RenderCenterMark(cam);

		background.RenderObjPosition(cam);

		fighters.RenderObjPosition(cam);
		fighters.RenderInputBuffer();

		projectiles.RenderObjPosition(cam);

		/*
		//player2
		olc::vi2d f2Pos = fighters.GetObjWorldPos(1);
		olc::vi2d f2ColPos = fighters.GetBodyWorldPos(1, BodyType::HEAD);

		//body collider render test
		olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(f2ColPos, cam), olc::CYAN);

		std::array<olc::vi2d, 4>f2ColQuads = fighters.GetBodyWorldQuad(1, BodyType::HEAD);
		olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(f2ColQuads[0], cam), olc::CYAN);
		olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(f2ColQuads[1], cam), olc::CYAN);
		olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(f2ColQuads[2], cam), olc::CYAN);
		olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(f2ColQuads[3], cam), olc::CYAN);

		size_t count = projectiles.GetObjCount();

		for (size_t i = 0; i < count; i++)
		{
			size_t ownerID = projectiles.GetObjCreationID(i);

			olc::vi2d projectilePos = projectiles.GetObjBoxColliderWorldPos(i);
			olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(projectilePos, cam), olc::CYAN);

			std::array<olc::vi2d, 4>projectileQuads = projectiles.GetObjBoxColliderWorldQuad(i);
			olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(projectileQuads[0], cam), olc::CYAN);
			olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(projectileQuads[1], cam), olc::CYAN);
			olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(projectileQuads[2], cam), olc::CYAN);
			olc::Renderer::ptrPGE->DrawLine(ScreenVector::GetScreenPosition(f2Pos, cam), ScreenVector::GetScreenPosition(projectileQuads[3], cam), olc::CYAN);

			//collision test
			if (DiagonalOverlap::yes(f2ColPos, f2ColQuads, projectilePos, projectileQuads))
			{
				int n = 0;
			}
		}
		*/
	}

	void FightScene::RenderStates(bool update)
	{
		background.RenderStates(cam, update);
		fighters.RenderStates(cam, update);
		fighters.RenderBoxColliders(cam);
		projectiles.RenderStates(cam, update);
	}
}