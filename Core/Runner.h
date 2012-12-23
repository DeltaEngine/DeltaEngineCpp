#pragma once
#include "Object.h"

namespace DeltaEngine { namespace Core
{
	// Allows classes to automatically run before any app code each frame (clearing, actors, physics,
	// etc.). Runners are executed in threads based on dependencies used in their constructors.
	// http://DeltaEngine.net/About/CodingStyle#Runners
	class CoreLibrary Runner : public virtual Object
	{
	public:
		virtual void Run() = 0;
	};
}}