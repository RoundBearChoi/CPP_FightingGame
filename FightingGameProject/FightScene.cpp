#include "FightScene.h"

namespace RB
{
	class Fighter_0_Idle;

	FightScene::FightScene(GameDataFactory* gameDataFactory)
	{
		IF_COUT{ std::cout << "constructing FightScene" << std::endl; };
		_gameDataFactory = gameDataFactory;

		_fighters = new FightersGroup(_gameDataFactory);
		_projectiles = new ProjectileGroup(_gameDataFactory);
		_impactEffects = new ImpactEffectsGroup(_gameDataFactory);
		_cam = new Camera(_gameDataFactory);
		
		DevSettings::renderMode = RenderMode::SPRITES_ONLY;
	}

	FightScene::~FightScene()
	{
		IF_COUT{ std::cout << "destructing FightScene" << std::endl; };

		delete _fighters;
		delete _projectiles;
		delete _impactEffects;

		if (damageDetector != nullptr)
		{
			delete damageDetector;
		}
	}

	void FightScene::InitScene()
	{
		_fighters->SetFighterInfo(olc::vi2d(-100, 0), PlayerType::PLAYER_1);
		_fighters->SetFighterInfo(olc::vi2d(100, 0), PlayerType::PLAYER_2);

		_fighters->SetState(0, State::NewState<Fighter_0_Idle>(_gameDataFactory, _fighters->GetObjData(0)));
		_fighters->SetState(1, State::NewState<Fighter_0_Idle>(_gameDataFactory, _fighters->GetObjData(1)));

		damageDetector = new DamageDetector(_fighters, _projectiles, _impactEffects);
	}

	void FightScene::UpdateScene()
	{
		GameData& gameData = *_gameDataFactory->GetGameData();

		damageDetector->Update();

		if (!SkipUpdate(*_fighters))
		{
			_fighters->UpdateStates();
		}
		
		_impactEffects->UpdateStates();

		std::vector<CreateProjectileMessage>* p1 = _fighters->GetProjectileQueues(0);
		std::vector<CreateProjectileMessage>* p2 = _fighters->GetProjectileQueues(1);
		_projectiles->CreateProjectiles(*p1);
		_projectiles->CreateProjectiles(*p2);
		p1->clear();
		p2->clear();

		_projectiles->UpdateStates();
	}

	void FightScene::RenderObjs()
	{
		RenderCenterMark(*_cam);

		_fighters->RenderObjPosition(*_cam);
		_fighters->RenderComponents();
		_projectiles->RenderObjPosition(*_cam);
		_impactEffects->RenderObjPosition(*_cam);
	}

	void FightScene::RenderStates(bool update)
	{
		_fighters->RenderStates(*_cam, update);
		_fighters->RenderBoxColliders(*_cam);
		_projectiles->RenderStates(*_cam, update);
		_impactEffects->RenderStates(*_cam, update);
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