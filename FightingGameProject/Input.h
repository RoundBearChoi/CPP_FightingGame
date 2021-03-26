#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "Key.h"

namespace RB
{
	class Input
	{
	private:
		//manual camera movement
		std::vector<Key> vecCamZoomIn;
		std::vector<Key> vecCamZoomOut;
		std::vector<Key> vecCamLeft;
		std::vector<Key> vecCamRight;

		//player1
		std::vector<Key> vecP1WeakPunch;
		std::vector<Key> vecP1StrongPunch;
		std::vector<Key> vecP1WeakKick;
		std::vector<Key> vecP1StrongKick;

		std::vector<Key> vecP1Up;
		std::vector<Key> vecP1Down;
		std::vector<Key> vecP1Left;
		std::vector<Key> vecP1Right;

		//player2
		std::vector<Key> vecP2WeakPunch;
		std::vector<Key> vecP2StrongPunch;
		std::vector<Key> vecP2WeakKick;
		std::vector<Key> vecP2StrongKick;

		std::vector<Key> vecP2Up;
		std::vector<Key> vecP2Down;
		std::vector<Key> vecP2Left;
		std::vector<Key> vecP2Right;

		//etc
		std::vector<Key> vecMouse0;
		std::vector<Key> vecShift;
		std::vector<Key> vecF8;
		std::vector<Key> vecF9;
		std::vector<Key> vecF10;
		std::vector<Key> vecF11;
		
	public:
		void UpdateInput()
		{
			UpdateKey(vecCamLeft, KeyType::CAM_LEFT, olc::Platform::ptrPGE->GetKey(olc::Key::J));
			UpdateKey(vecCamRight, KeyType::CAM_RIGHT, olc::Platform::ptrPGE->GetKey(olc::Key::L));
			UpdateKey(vecCamZoomIn, KeyType::CAM_ZOOM_IN, olc::Platform::ptrPGE->GetKey(olc::Key::I));
			UpdateKey(vecCamZoomOut, KeyType::CAM_ZOOM_OUT, olc::Platform::ptrPGE->GetKey(olc::Key::K));

			UpdateKey(vecP1WeakPunch, KeyType::P1_WeakPunch, olc::Platform::ptrPGE->GetKey(olc::Key::T));
			UpdateKey(vecP1StrongPunch, KeyType::P1_StrongPunch, olc::Platform::ptrPGE->GetKey(olc::Key::Y));
			UpdateKey(vecP1WeakKick, KeyType::P1_WeakKick, olc::Platform::ptrPGE->GetKey(olc::Key::G));
			UpdateKey(vecP1StrongKick, KeyType::P1_StrongKick, olc::Platform::ptrPGE->GetKey(olc::Key::H));

			UpdateKey(vecP1Up, KeyType::P1_UP, olc::Platform::ptrPGE->GetKey(olc::Key::W));
			UpdateKey(vecP1Down, KeyType::P1_DOWN, olc::Platform::ptrPGE->GetKey(olc::Key::S));
			UpdateKey(vecP1Left, KeyType::P1_LEFT, olc::Platform::ptrPGE->GetKey(olc::Key::A));
			UpdateKey(vecP1Right, KeyType::P1_RIGHT, olc::Platform::ptrPGE->GetKey(olc::Key::D));

			UpdateKey(vecP2WeakPunch, KeyType::P2_WeakPunch, olc::Platform::ptrPGE->GetKey(olc::Key::NP7));
			UpdateKey(vecP2StrongPunch, KeyType::P2_StrongPunch, olc::Platform::ptrPGE->GetKey(olc::Key::NP8));
			UpdateKey(vecP2WeakKick, KeyType::P2_WeakKick, olc::Platform::ptrPGE->GetKey(olc::Key::NP4));
			UpdateKey(vecP2StrongKick, KeyType::P2_StrongKick, olc::Platform::ptrPGE->GetKey(olc::Key::NP5));

			UpdateKey(vecP2Up, KeyType::P2_UP, olc::Platform::ptrPGE->GetKey(olc::Key::UP));
			UpdateKey(vecP2Down, KeyType::P2_DOWN, olc::Platform::ptrPGE->GetKey(olc::Key::DOWN));
			UpdateKey(vecP2Left, KeyType::P2_LEFT, olc::Platform::ptrPGE->GetKey(olc::Key::LEFT));
			UpdateKey(vecP2Right, KeyType::P2_RIGHT, olc::Platform::ptrPGE->GetKey(olc::Key::RIGHT));

			UpdateKey(vecMouse0, KeyType::MOUSE_0, olc::Platform::ptrPGE->GetMouse(0));
			UpdateKey(vecShift, KeyType::SHIFT, olc::Platform::ptrPGE->GetKey(olc::Key::SHIFT));
			UpdateKey(vecF8, KeyType::F8, olc::Platform::ptrPGE->GetKey(olc::Key::F8));
			UpdateKey(vecF9, KeyType::F9, olc::Platform::ptrPGE->GetKey(olc::Key::F9));
			UpdateKey(vecF10, KeyType::F10, olc::Platform::ptrPGE->GetKey(olc::Key::F10));
			UpdateKey(vecF11, KeyType::F11, olc::Platform::ptrPGE->GetKey(olc::Key::F11));

			//olc::Renderer::ptrPGE->DrawString({ 0, 35 }, "p2 left: " + std::to_string(vecP2Left.size()));
			//olc::Renderer::ptrPGE->DrawString({ 0, 35 + 12 }, "p1 jab: " + std::to_string(vecP1WeakPunch.size()));
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
			gameData.key_j = GetUnprocessedKey(vecCamLeft);
			gameData.key_l = GetUnprocessedKey(vecCamRight);
			gameData.key_i = GetUnprocessedKey(vecCamZoomIn);
			gameData.key_k = GetUnprocessedKey(vecCamZoomOut);

			gameData.key_y = GetUnprocessedKey(vecP1StrongPunch);
			gameData.key_t = GetUnprocessedKey(vecP1WeakPunch);
			gameData.key_g = GetUnprocessedKey(vecP1WeakKick);
			gameData.key_h = GetUnprocessedKey(vecP1StrongKick);

			gameData.key_w = GetUnprocessedKey(vecP1Up);
			gameData.key_s = GetUnprocessedKey(vecP1Down);
			gameData.key_a = GetUnprocessedKey(vecP1Left);
			gameData.key_d = GetUnprocessedKey(vecP1Right);

			gameData.key_np7 = GetUnprocessedKey(vecP2StrongPunch);
			gameData.key_np8 = GetUnprocessedKey(vecP2WeakPunch);
			gameData.key_np4 = GetUnprocessedKey(vecP2WeakKick);
			gameData.key_np5 = GetUnprocessedKey(vecP2StrongKick);

			gameData.key_up = GetUnprocessedKey(vecP2Up);
			gameData.key_down = GetUnprocessedKey(vecP2Down);
			gameData.key_left = GetUnprocessedKey(vecP2Left);
			gameData.key_right = GetUnprocessedKey(vecP2Right);

			gameData.key_mouse0 = GetUnprocessedKey(vecMouse0);
			gameData.key_shift = GetUnprocessedKey(vecShift);
			gameData.key_f8 = GetUnprocessedKey(vecF8);
			gameData.key_f9 = GetUnprocessedKey(vecF9);
			gameData.key_f10 = GetUnprocessedKey(vecF10);
			gameData.key_f11 = GetUnprocessedKey(vecF11);
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

			ClearReleasedKeys(vecP1WeakPunch);
			ClearReleasedKeys(vecP1StrongPunch);
			ClearReleasedKeys(vecP1WeakKick);
			ClearReleasedKeys(vecP1StrongKick);

			ClearReleasedKeys(vecP1Up);
			ClearReleasedKeys(vecP1Down);
			ClearReleasedKeys(vecP1Left);
			ClearReleasedKeys(vecP1Right);

			ClearReleasedKeys(vecP2WeakPunch);
			ClearReleasedKeys(vecP2StrongPunch);
			ClearReleasedKeys(vecP2WeakKick);
			ClearReleasedKeys(vecP2StrongKick);

			ClearReleasedKeys(vecP2Up);
			ClearReleasedKeys(vecP2Down);
			ClearReleasedKeys(vecP2Left);
			ClearReleasedKeys(vecP2Right);

			ClearReleasedKeys(vecMouse0);
			ClearReleasedKeys(vecShift);
			ClearReleasedKeys(vecF8);
			ClearReleasedKeys(vecF9);
			ClearReleasedKeys(vecF10);
			ClearReleasedKeys(vecF11);
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