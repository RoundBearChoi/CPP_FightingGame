#pragma once
#include "olcPixelGameEngine.h"
#include "GameData.h"
#include "DevSettings.h"
#include "Camera.h"
#include "RelativeVector.h"

namespace RB
{
	class Scene
	{
	protected:
		int ID = 0;

	public:
		Camera cam;

		virtual void InitScene() = 0;
		virtual void UpdateScene(olc::PixelGameEngine* ptrEngine, GameData& gameData) = 0;
		virtual void RenderObjPosition(olc::PixelGameEngine* ptrEngine) = 0;
		virtual void RenderStates(bool update, olc::PixelGameEngine* ptrEngine) = 0;

		virtual ~Scene()
		{
			IF_COUT{ std::cout << "destructing Scene (virtual): " << ID << std::endl; }
		}

		void RenderCenterMark(olc::PixelGameEngine* ptrEngine, olc::vi2d camPos, float zoomScale)
		{
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
		}
	};
}