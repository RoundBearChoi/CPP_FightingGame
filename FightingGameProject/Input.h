#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "Key.h"

namespace RB
{
	class Input
	{
	private:
		std::vector<Key> vecCamZoomIn;
		std::vector<Key> vecCamZoomOut;
		std::vector<Key> vecCamLeft;
		std::vector<Key> vecCamRight;

		std::vector<Key> vecP1Jab;
		std::vector<Key> vecP1Left;
		std::vector<Key> vecP1Right;
		std::vector<Key> vecP1Up;
		std::vector<Key> vecP1Down;

		std::vector<Key> vecMouse0;
		
	public:
		void UpdateInput()
		{
			UpdateKey(vecMouse0, KeyType::MOUSE_0, olc::Platform::ptrPGE->GetMouse(0));

			UpdateKey(vecCamLeft, KeyType::CAM_LEFT, olc::Platform::ptrPGE->GetKey(olc::Key::LEFT));
			UpdateKey(vecCamRight, KeyType::CAM_RIGHT, olc::Platform::ptrPGE->GetKey(olc::Key::RIGHT));
			UpdateKey(vecCamZoomIn, KeyType::CAM_ZOOM_IN, olc::Platform::ptrPGE->GetKey(olc::Key::UP));
			UpdateKey(vecCamZoomOut, KeyType::CAM_ZOOM_OUT, olc::Platform::ptrPGE->GetKey(olc::Key::DOWN));

			UpdateKey(vecP1Jab, KeyType::P1_JAB, olc::Platform::ptrPGE->GetKey(olc::Key::T));
			UpdateKey(vecP1Left, KeyType::P1_LEFT, olc::Platform::ptrPGE->GetKey(olc::Key::A));
			UpdateKey(vecP1Right, KeyType::P1_RIGHT, olc::Platform::ptrPGE->GetKey(olc::Key::D));
			UpdateKey(vecP1Up, KeyType::P1_UP, olc::Platform::ptrPGE->GetKey(olc::Key::W));
			UpdateKey(vecP1Down, KeyType::P1_DOWN, olc::Platform::ptrPGE->GetKey(olc::Key::S));

			if (vecMouse0.size() > 0)
			{
				int n = 0;
			}
		}

		void UpdateKey(std::vector<Key>& vec, KeyType _keyType, olc::HWButton button)
		{
			Key newKey;
			newKey.keyType = _keyType;

			if (button.bPressed)
			{
				vec.push_back(newKey);
			}

			if (button.bReleased)
			{
				for (int32_t i = 0; i < vec.size(); i++)
				{
					vec[i].released = true;
				}
			}
		}

		void UpdateGameData(GameData& gameData)
		{
			gameData.mouse0 = GetUnprocessedKey(vecMouse0);

			gameData.left = GetUnprocessedKey(vecCamLeft);
			gameData.right = GetUnprocessedKey(vecCamRight);
			gameData.up = GetUnprocessedKey(vecCamZoomIn);
			gameData.down = GetUnprocessedKey(vecCamZoomOut);

			gameData.t = GetUnprocessedKey(vecP1Jab);
			gameData.a = GetUnprocessedKey(vecP1Left);
			gameData.d = GetUnprocessedKey(vecP1Right);
			gameData.w = GetUnprocessedKey(vecP1Up);
			gameData.s = GetUnprocessedKey(vecP1Down);
		}

		Key* GetUnprocessedKey(std::vector<Key>& vec)
		{
			for (int i = 0; i < vec.size(); i++)
			{
				if (!vec[i].processed)
				{
					return &vec[i];
				}
			}

			return nullptr;
		}

		void ClearKeyQueues()
		{
			ClearReleasedKeys(vecMouse0);

			ClearReleasedKeys(vecCamLeft);
			ClearReleasedKeys(vecCamRight);
			ClearReleasedKeys(vecCamZoomIn);
			ClearReleasedKeys(vecCamZoomOut);

			ClearReleasedKeys(vecP1Jab);
			ClearReleasedKeys(vecP1Left);
			ClearReleasedKeys(vecP1Right);
			ClearReleasedKeys(vecP1Up);
			ClearReleasedKeys(vecP1Down);
		}

		void ClearReleasedKeys(std::vector<Key>& vec)
		{
			if (vec.size() > 0)
			{
				if (vec[0].released)
				{
					vec.clear();
				}
			}
		}
	};
}