#pragma once
#include <vector>
#include "StopCountData.h"

namespace RB
{
	class Updater
	{
	protected:
		size_t _updaterUpdateCount = 0;
		int32_t _stopCount = 0;
		std::vector<StopCountData> _vecStopCounts;

	public:
		virtual void CustomUpdate() = 0;

		virtual void UpdateUpdateCount()
		{
			_updaterUpdateCount++;

			if (_updaterUpdateCount >= SIZE_MAX)
			{
				_updaterUpdateCount = 0;
			}
		}

		virtual void AddStopCountQueue(StopCountData data)
		{
			_vecStopCounts.push_back(data);
		}

		virtual void ProcessStopCounts()
		{
			std::vector<size_t> deleteIndexes;

			for (size_t i = 0; i < _vecStopCounts.size(); i++)
			{
				if (_vecStopCounts[i].oneFrameSkipped)
				{
					_stopCount += _vecStopCounts[i].stopCount;
					deleteIndexes.push_back(i);
				}
			
				if (!_vecStopCounts[i].oneFrameSkipped)
				{
					_vecStopCounts[i].oneFrameSkipped = true;
				}
			}

			for (size_t i = 0; i < deleteIndexes.size(); i++)
			{
				if (_vecStopCounts.size() > deleteIndexes[i])
				{
					_vecStopCounts.erase(_vecStopCounts.begin() + deleteIndexes[i]);
				}
			}
		}
	};
}