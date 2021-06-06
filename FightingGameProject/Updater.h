#pragma once

namespace RB
{
	class Updater
	{
	protected:
		size_t _updaterUpdateCount = 0;
		int32_t _stopCount = 0;

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

		virtual void ClearStopCount()
		{
			_stopCount = 0;
		}

		virtual void AddStopCount(int32_t count)
		{
			_stopCount += count;
		}
	};
}