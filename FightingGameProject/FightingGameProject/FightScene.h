#pragma once
#include "Scene.h"
#include "Fighters.h"
#include "GameWindow.h"
#include "RelativeVector.h"

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
			olc::vi2d pos0{ -220, 0 };
			olc::vi2d pos1{ 220, 0 };

			fighters.SetFighterInfo(0, pos0);
			fighters.SetFighterInfo(1, pos1);
		}

		void UpdateScene(olc::PixelGameEngine* ptrEngine, GameData& gameData) override
		{
			cam.Update(gameData);
		}

		void RenderObjPosition(olc::PixelGameEngine* ptrEngine) override
		{
			//camera position and zoom
			olc::vi2d camPos = cam.GetPosition();
			float zoomScale = cam.GetZoom();

			//centermark
			olc::vi2d bottom{ 0, 7 };
			olc::vi2d top{ 0, -7 };
			olc::vi2d left{ -7, 0 };
			olc::vi2d right{ 7, 0 };

			olc::vi2d relativeTop = RelativeVector::Get(top, camPos, zoomScale);
			olc::vi2d relativeBottom = RelativeVector::Get(bottom, camPos, zoomScale);
			olc::vi2d relativeLeft = RelativeVector::Get(left, camPos, zoomScale);
			olc::vi2d relativeRight = RelativeVector::Get(right, camPos, zoomScale);

			ptrEngine->DrawLine(relativeTop, relativeBottom, olc::GREEN);
			ptrEngine->DrawLine(relativeLeft, relativeRight, olc::GREEN);

			//objs
			fighters.RenderObjPosition(ptrEngine, camPos, zoomScale);
		}

		void RenderStates(bool update, olc::PixelGameEngine* ptrEngine) override
		{

		}
	};
}