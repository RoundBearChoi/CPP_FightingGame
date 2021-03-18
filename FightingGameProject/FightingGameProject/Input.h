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
		std::vector<Key> vecP1Right;
		
	public:
		void UpdateInput()
		{
			UpdateKey(vecCamLeft, KeyType::CAM_LEFT, olc::Key::LEFT);
			UpdateKey(vecCamRight, KeyType::CAM_RIGHT, olc::Key::RIGHT);
			UpdateKey(vecCamZoomIn, KeyType::CAM_ZOOM_IN, olc::Key::UP);
			UpdateKey(vecCamZoomOut, KeyType::CAM_ZOOM_OUT, olc::Key::DOWN);

			UpdateKey(vecP1Jab, KeyType::P1_JAB, olc::Key::T);
			UpdateKey(vecP1Right, KeyType::P1_RIGHT, olc::Key::D);
		}

		void UpdateKey(std::vector<Key>& vec, KeyType _keyType, olc::Key targetKey)
		{
			Key newKey;
			newKey.keyType = _keyType;

			if (olc::Platform::ptrPGE->GetKey(targetKey).bPressed)
			{
				vec.push_back(newKey);
			}

			if (olc::Platform::ptrPGE->GetKey(targetKey).bReleased)
			{
				for (int32_t i = 0; i < vec.size(); i++)
				{
					vec[i].released = true;
				}
			}
		}

		void UpdateGameData(GameData& gameData)
		{
			gameData.left = CheckRelease(vecCamLeft);
			gameData.right = CheckRelease(vecCamRight);
			gameData.up = CheckRelease(vecCamZoomIn);
			gameData.down = CheckRelease(vecCamZoomOut);

			gameData.t = GetUnprocessedKey(vecP1Jab);
			gameData.d = CheckRelease(vecP1Right);
		}

		bool CheckRelease(std::vector<Key>& vec)
		{
			for (int32_t i = 0; i < vec.size(); i++)
			{
				if (!vec[i].released)
				{
					return true;
				}
			}

			return false;
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
			ClearReleasedKeys(vecCamLeft);
			ClearReleasedKeys(vecCamRight);
			ClearReleasedKeys(vecCamZoomIn);
			ClearReleasedKeys(vecCamZoomOut);

			ClearReleasedKeys(vecP1Right);
			ClearReleasedKeys(vecP1Jab);
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