#pragma once

namespace RB
{
	enum class KeyType
	{
		NONE,

		CAM_ZOOM_IN,
		CAM_ZOOM_OUT,
		CAM_LEFT,
		CAM_RIGHT,

		P1_WeakPunch,
		P1_StrongPunch,
		P1_WeakKick,
		P1_StrongKick,

		P1_UP,
		P1_DOWN,
		P1_LEFT,
		P1_RIGHT,

		P2_WeakPunch,
		P2_StrongPunch,
		P2_WeakKick,
		P2_StrongKick,

		P2_UP,
		P2_DOWN,
		P2_LEFT,
		P2_RIGHT,

		MOUSE_0, //leftclick
		MOUSE_1, //rightclick
		SHIFT,
		F9,
		F10,
		F11,
	};
}