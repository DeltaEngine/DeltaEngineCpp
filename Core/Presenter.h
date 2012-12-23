#pragma once
#include "Runner.h"

namespace DeltaEngine { namespace Core
{
	// While Runners execute before app code is run, presenters are run after app code has been
	// executed at the end of each frame. Presenters are quick and executed in the same thread.
	// http://DeltaEngine.net/About/CodingStyle#Presenters
	class CoreLibrary Presenter : public virtual Runner
	{
	public:
		virtual void Present() = 0;
	};
}}