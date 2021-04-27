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

		if (damageDetector != nullptr)
		{
			delete damageDetector;
		}
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

		damageDetector = new DamageDetector(&fighters, &projectiles, &impactEffects);
	}

	void FightScene::UpdateScene(GameData& gameData)
	{
		damageDetector->Update();

		background.UpdateStates(gameData);
		background.UpdateOffset(cam);

		if (!SkipUpdate(fighters))
		{
			fighters.UpdateStates(gameData);
		}
		else
		{
			int n = 0;
		}
		
		impactEffects.UpdateStates(gameData);

		std::vector<CreateProjectileMessage>* p1 = fighters.GetProjectileQueues(0);
		std::vector<CreateProjectileMessage>* p2 = fighters.GetProjectileQueues(1);
		projectiles.CreateProjectiles(*p1);
		projectiles.CreateProjectiles(*p2);
		p1->clear();
		p2->clear();

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
		fighters.RenderStates(cam, update);
		fighters.RenderBoxColliders(cam);
		projectiles.RenderStates(cam, update);
		impactEffects.RenderStates(cam, update);
	}

	bool FightScene::SkipUpdate(ObjGroup& group)
	{
		bool skip = false;

		for (size_t i = 0; i < group.vecSlowMotion.size(); i++)
		{
			if (group.vecSlowMotion[i].SkipUpdate())
			{
				size_t max = (size_t)group.vecSlowMotion[i].maxCount * (size_t)group.vecSlowMotion[i].interval;
				if (group.vecSlowMotion[i].updateCount <= max)
				{
					skip = true;
					break;
				}
			}
		}

		for (size_t i = 0; i < group.vecSlowMotion.size(); i++)
		{
			group.vecSlowMotion[i].updateCount++;
		}

		if (group.vecSlowMotion.size() > 0)
		{
			size_t end = (size_t)group.vecSlowMotion[0].maxCount * (size_t)group.vecSlowMotion[0].interval;
			if (group.vecSlowMotion[0].updateCount > end)
			{
				group.vecSlowMotion.erase(group.vecSlowMotion.begin());
			}
		}

		return skip;
	}
}