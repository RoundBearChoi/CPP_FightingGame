#pragma once

namespace RB
{
	class Updater
	{
	protected:
		size_t _updaterUpdateCount = 0;

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
	};
}