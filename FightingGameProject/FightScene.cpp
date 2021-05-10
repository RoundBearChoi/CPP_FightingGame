#include "FightScene.h"

namespace RB
{
	FightScene::FightScene(GameDataFactory* gameDataFactory)
	{
		IF_COUT{ std::cout << "constructing FightScene" << std::endl; };
		_gameDataFactory = gameDataFactory;
		_cam = new Camera(_gameDataFactory);
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
		fighters.SetFighterInfo(olc::vi2d(-100, 0), PlayerType::PLAYER_1);
		fighters.SetFighterInfo(olc::vi2d(100, 0), PlayerType::PLAYER_2);

		fighters.SetState(0, State::NewState<Fighter_0_Idle>());
		fighters.SetState(1, State::NewState<Fighter_0_Idle>());

		damageDetector = new DamageDetector(&fighters, &projectiles, &impactEffects);
	}

	void FightScene::UpdateScene()
	{
		GameData& gameData = *_gameDataFactory->GetGameData();

		damageDetector->Update();

		if (!SkipUpdate(fighters))
		{
			fighters.UpdateStates(gameData);
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
		RenderCenterMark(*_cam);

		fighters.RenderObjPosition(*_cam);
		fighters.RenderComponents();
		projectiles.RenderObjPosition(*_cam);
		impactEffects.RenderObjPosition(*_cam);
	}

	void FightScene::RenderStates(bool update)
	{
		fighters.RenderStates(*_cam, update);
		fighters.RenderBoxColliders(*_cam);
		projectiles.RenderStates(*_cam, update);
		impactEffects.RenderStates(*_cam, update);
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