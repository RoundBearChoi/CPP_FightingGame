#pragma once

namespace RB
{
	enum class KeyType
	{
		NONE,

		MOUSE_0, //leftclick
		MOUSE_1, //rightclick

		P1_WeakPunch,
		P1_StrongPunch,
		P1_WeakKick,
		P1_StrongKick,
		P1_UP,
		P1_DOWN,
		P1_LEFT,
		P1_RIGHT,

		CAM_ZOOM_IN,
		CAM_ZOOM_OUT,
		CAM_LEFT,
		CAM_RIGHT,
	};
}