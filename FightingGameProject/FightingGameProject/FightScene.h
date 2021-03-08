#pragma once
#include "Scene.h"
#include "Fighters.h"

//states for game scene
//#include "BackgroundIdle.h"
//#include "PlayerGameStart.h"
//#include "PlayerIdle.h"
//#include "PlayerMoveLeft.h"
//#include "PlayerMoveRight.h"
//#include "ShitGenerator.h"
//#include "ShitPosition.h"
//#include "ShitMoveDown.h"
//#include "ShitUpSplash.h"
//#include "ShitCenterSplash.h"
//#include "PlayerDeath.h"
//#include "YesOrNo.h"

namespace RB
{
	class FightScene : public Scene
	{
	private:
		Fighters fighters;

	public:
		FightScene(size_t _id)
		{
			IF_COUT{ std::cout << "constructing FightScene:" << _id << std::endl; }

			ID = _id;
		}

		~FightScene() override
		{
			IF_COUT{ std::cout << "destructing FightScene: " << ID << std::endl; }
		}

		void InitScene() override
		{
			olc::vf2d pos0{ 0.0f, 0.0f };
			olc::vf2d pos1{ 10.0f, 0.0f };

			fighters.AddNewFighter(0, pos0);
			fighters.AddNewFighter(1, pos1);

			//ObjSpecs background;
			//ObjSpecs player;
			//ObjSpecs shitgroup;
			//
			//background.width = 600.0f;
			//background.height = 700.0f;
			//background.objTag = ObjTag::NONE;
			//background.offsetType = OffsetType::NONE;
			//background.decalIndex = (int)GameSpriteType::background;
			//
			//player.width = 50.0f;
			//player.height = 80.0f;
			//player.objTag = ObjTag::PLAYER;
			//player.offsetType = OffsetType::BOTTOM_CENTER;
			//player.decalIndex = (int)GameSpriteType::playerbox_green;
			//
			//shitgroup.width = 0.0f;
			//shitgroup.height = 0.0f;
			//shitgroup.objTag = ObjTag::SHIT_GENERATOR;
			//shitgroup.offsetType = OffsetType::CENTER_CENTER;
			//shitgroup.decalIndex = (int)GameSpriteType::redbox_10x10;
			//
			//objList.CreateObj<BackgroundIdle>(background);
			//objList.CreateObj<PlayerGameStart>(player);
			//objList.CreateObj<ShitGenerator>(shitgroup);
		}

		void UpdateScene(olc::PixelGameEngine* ptrEngine, GameData& gameData) override
		{

		}

		void RenderObjPosition(olc::PixelGameEngine* ptrEngine) override
		{
			fighters.RenderObjPosition();
		}

		void RenderStates(bool update, olc::PixelGameEngine* ptrEngine) override
		{

		}
	};
}