#pragma once
#include "Object.h"

namespace DeltaEngine { namespace Core
{
	// Provides Ticks for the Time class to measure time differences between frames. Can easily be
	// mocked for tests and replaced with platforms framework classes for better accuracy and speed.
	class CoreLibrary ElapsedTime : public virtual Object
	{
	public:
		virtual long long GetTicks() = 0;
		virtual long long GetTicksPerSecond() const = 0;
	};
}}