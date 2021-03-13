#include "Scene.h"
#include "DevSettings.h"
#include "RelativeVector.h"

namespace RB
{
	Scene::~Scene()
	{
		IF_COUT{ std::cout << "destructing Scene (virtual)" << std::endl; }
	}

	void Scene::RenderCenterMark(olc::PixelGameEngine* ptrEngine, Camera& cam)
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
}