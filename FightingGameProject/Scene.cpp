#include "Scene.h"

namespace RB
{
	Scene::~Scene()
	{
		IF_COUT{ std::cout << "destructing Scene (virtual)" << std::endl; };

		delete _cam;
	}

	void Scene::ShowZeroPosition(Camera& cam)
	{
		olc::vi2d bottom{ 0, 7 };
		olc::vi2d top{ 0, -7 };
		olc::vi2d left{ -7, 0 };
		olc::vi2d right{ 7, 0 };

		olc::vi2d relativeTop = ScreenVector::GetScreenPosition(top, cam);
		olc::vi2d relativeBottom = ScreenVector::GetScreenPosition(bottom, cam);
		olc::vi2d relativeLeft = ScreenVector::GetScreenPosition(left, cam);
		olc::vi2d relativeRight = ScreenVector::GetScreenPosition(right, cam);

		if (DevSettings::renderMode == RenderMode::DEBUG_ONLY || DevSettings::renderMode == RenderMode::SPRITES_AND_DEBUG)
		{
			olc::Renderer::ptrPGE->DrawLine(relativeTop, relativeBottom, olc::GREEN);
			olc::Renderer::ptrPGE->DrawLine(relativeLeft, relativeRight, olc::GREEN);
		}
	}
}