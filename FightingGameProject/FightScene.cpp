#include "FightScene.h"

namespace RB
{
	FightScene::FightScene()
	{
		IF_COUT{ std::cout << "constructing FightScene" << std::endl; };
		DevSettings::renderMode = RenderMode::SPRITES_ONLY;
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

	void FightScene::UpdateScene(GameData& gameData)
	{
		for (int32_t i = 0; i < 2; i++)
		{
			//projectiles vs player collision
			size_t projIndex = 0;
			olc::vi2d projCollisionPoint;

			if (ProjectileCollision::IsColliding(i, fighters, projectiles, projIndex, projCollisionPoint))
			{
				projectiles.DeleteObj(projIndex);
				fighters.MakeNewState<Fighter_0_HitReaction_Side>(i);
				impactEffects.CreateEffect(ImpactEffectType::HIT_0, projCollisionPoint);
			}

			//body part vs body part collision
			olc::vi2d bodyPartCollisionPoint;
			DamageData damageData;
			int32_t enemy = 0;

			if (i == 0)
			{
				enemy = 1;
			}
			
			if (BodyPartCollision::IsColliding(enemy, fighters, bodyPartCollisionPoint, damageData))
			{
				impactEffects.CreateEffect(ImpactEffectType::HIT_0, bodyPartCollisionPoint);

				if (damageData.upPush != 0)
				{
					fighters.AddJumpProcessor(i, damageData.upPush, damageData.sidePush);
					fighters.MakeNewState<Fighter_0_HitReaction_Up>(i);
				}
				else
				{
					fighters.MakeNewState<Fighter_0_HitReaction_Side>(i);
				}
			}
		}

		//update objs
		background.UpdateStates(gameData);
		background.UpdateOffset(cam);
		fighters.UpdateStates(gameData);
		impactEffects.UpdateStates(gameData);

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
		fighters.RenderComponents();
		projectiles.RenderObjPosition(cam);
		impactEffects.RenderObjPosition(cam);
	}

	void FightScene::RenderStates(bool update)
	{
		//background.RenderStates(cam, update);
		fighters.RenderStates(cam, update);
		fighters.RenderBoxColliders(cam);
		projectiles.RenderStates(cam, update);
		impactEffects.RenderStates(cam, update);
	}
}