#pragma once
#include "ElapsedTime.h"
#include "Hypodermic/AutowiredConstructor.h"
#include <Windows.h>

namespace DeltaEngine { namespace Core
{
	// Provides ticks for the Time class via QueryPerformanceCounter. This class is
	// usually the fallback if nothing else has been registered for the ElapsedTime interface.
	class CoreLibrary StopwatchTime : public ElapsedTime
	{
	public:
		typedef Hypodermic::AutowiredConstructor<StopwatchTime()> AutowiredSignature;
		StopwatchTime();

		long long GetTicks();
		long long GetTicksPerSecond() const;

	private:
		_LARGE_INTEGER start;
		_LARGE_INTEGER current;
		_LARGE_INTEGER frequency;
	};
}}