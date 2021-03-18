#pragma once
#include "KeyType.h"

namespace RB
{
	class Key
	{
	public:
		KeyType keyType = KeyType::NONE;
		bool processed = false;
		bool released = false;
	};
}