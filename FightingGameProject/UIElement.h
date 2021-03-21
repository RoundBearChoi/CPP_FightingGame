#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class UIElement
	{
	public:
		olc::vi2d topLeft = { 0, 0 };
		int32_t width = 0;
		int32_t height = 0;
		olc::Decal* ptrDecal = nullptr;
		olc::Pixel tint = olc::WHITE;
		std::string path = "none";
		size_t hash = 0;

		void SetHash()
		{
			IF_COUT{ std::cout << "hashing: " << path << std::endl; }
			hash = std::hash<std::string>{}(path);
			IF_COUT{ std::cout << hash << std::endl; };
		}

		void SetDecal()
		{
			ptrDecal = SpriteLoader::ptr->FindDecal(hash, (size_t)SpriteType::BOXCOLLIDER_EDITOR_UI);

			if (ptrDecal == nullptr)
			{
				IF_COUT{ std::cout << "decal not found" << std::endl; }
			}
		}

		bool MouseHovering(olc::vi2d& mousePos)
		{
			if (width == 0 || height == 0)
			{
				return false;
			}
			else if (mousePos.x >= topLeft.x && mousePos.x <= topLeft.x + width)
			{
				if (mousePos.y >= topLeft.y && mousePos.y <= topLeft.y + height)
				{
					return true;
				}
			}

			return false;
		}

		void GreenTintOnHover(olc::vi2d& mousePos)
		{
			if (MouseHovering(mousePos))
			{
				tint = olc::GREEN;
			}
			else
			{
				tint = olc::WHITE;
			}
		}

		bool Clicked(olc::vi2d& mousePos, GameData& gameData)
		{
			if (MouseHovering(mousePos))
			{
				if (gameData.key_mouse0)
				{
					gameData.key_mouse0->processed = true;
					return true;
				}
			}

			return false;
		}
	};
}