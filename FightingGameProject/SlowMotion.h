#pragma once
#include "ObjGroup.h"

namespace RB
{
	class SlowMotion
	{
	private:
		ObjGroup* _targetGroup = nullptr;

	public:
		SlowMotion(ObjGroup* targetGroup)
		{
			_targetGroup = targetGroup;
		}

		bool SkipUpdate()
		{
			bool skip = false;

			for (size_t i = 0; i < _targetGroup->vecSlowMotion.size(); i++)
			{
				if (_targetGroup->vecSlowMotion[i].SkipUpdate())
				{
					size_t max = (size_t)_targetGroup->vecSlowMotion[i].maxCount * (size_t)_targetGroup->vecSlowMotion[i].interval;
					if (_targetGroup->vecSlowMotion[i].updateCount <= max)
					{
						skip = true;
						break;
					}
				}
			}

			for (size_t i = 0; i < _targetGroup->vecSlowMotion.size(); i++)
			{
				_targetGroup->vecSlowMotion[i].updateCount++;
			}

			if (_targetGroup->vecSlowMotion.size() > 0)
			{
				size_t end = (size_t)_targetGroup->vecSlowMotion[0].maxCount * (size_t)_targetGroup->vecSlowMotion[0].interval;
				if (_targetGroup->vecSlowMotion[0].updateCount > end)
				{
					_targetGroup->vecSlowMotion.erase(_targetGroup->vecSlowMotion.begin());
				}
			}

			return skip;
		}
	};
}