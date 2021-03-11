#pragma once
#include "olcPixelGameEngine.h"
#include "GameData.h"
#include "DevSettings.h"
#include "Camera.h"
#include "RelativeVector.h"
#include "DecalLoader.h"

namespace RB
{
	class Scene
	{
	public:
		DecalLoader* ptrDecalLoader;
		Camera cam;

		virtual void InitScene() = 0;
		virtual void Update(GameData& gameData) = 0;
		virtual void RenderObjPosition(olc::PixelGameEngine* ptrEngine) = 0;
		virtual void RenderStates(olc::PixelGameEngine* ptrEngine, bool update) = 0;

		virtual ~Scene()
		{
			IF_COUT{ std::cout << "destructing Scene (virtual)" << std::endl; }
		}

		void RenderCenterMark(olc::PixelGameEngine* ptrEngine, Camera& cam)
		{
			olc::vi2d bottom{ 0, 7 };
			olc::vi2d top{ 0, -7 };
			olc::vi2d left{ -7, 0 };
			olc::vi2d right{ 7, 0 };

			olc::vi2d relativeTop = RelativeVector::GetPosition(top, cam);
			olc::vi2d relativeBottom = RelativeVector::GetPosition(bottom, cam);
			olc::vi2d relativeLeft = RelativeVector::GetPosition(left, cam);
			olc::vi2d relativeRight = RelativeVector::GetPosition(right, cam);

			ptrEngine->DrawLine(relativeTop, relativeBottom, olc::GREEN);
			ptrEngine->DrawLine(relativeLeft, relativeRight, olc::GREEN);
		}
	};
}