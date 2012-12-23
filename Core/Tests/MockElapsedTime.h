#pragma once
#include "Core\ElapsedTime.h"
#include <Windows.h>

namespace DeltaEngine { namespace Core { namespace Tests
{
	class MockElapsedTime : public ElapsedTime
	{
	public:
		MockElapsedTime()
		{
			ticks = 0;
		}

		long long GetTicks()
		{
			return ticks++;
		}

		long long GetTicksPerSecond() const
		{
			return 10;
		}

	private:
		int ticks;
	};
}}}