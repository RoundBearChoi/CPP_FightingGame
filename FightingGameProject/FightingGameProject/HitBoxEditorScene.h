#pragma once
#include "Scene.h"
#include "GameData.h"

namespace RB
{
	class HitBoxEditorScene : public Scene
	{
	private:
		//Fighters fighters;
		//Background background;

	public:
		HitBoxEditorScene()
		{
			IF_COUT{ std::cout << "constructing HitBoxEditorScene" << std::endl; }
		}

		~HitBoxEditorScene() override
		{
			IF_COUT{ std::cout << "destructing HitBoxEditorScene" << std::endl; }
		}

		void InitScene() override
		{

		}

		void Update(GameData& gameData) override
		{
		}

		void RenderObjPosition() override
		{
			olc::Renderer::ptrPGE->DrawString({ 0, 20 }, "HitBoxEditor", olc::WHITE);

			RenderCenterMark(cam);
		}

		void RenderStates(bool update) override
		{

		}
	};
}