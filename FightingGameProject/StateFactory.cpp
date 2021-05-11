#include "StateFactory.h"

namespace RB
{
	StateFactory* StateFactory::ptr = nullptr;

	StateFactory::StateFactory()
	{

	}

	StateFactory::~StateFactory()
	{
		delete Creator_Fighter_0_Idle;
	}
}