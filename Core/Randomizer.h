#pragma once
#include "Object.h"

namespace DeltaEngine { namespace Core
{
	// Returns an integer greater than or equal to min and strictly less than max
	class CoreLibrary Randomizer
	{
	public:
		virtual int Get(int min, int max) = 0;
		virtual float Get(float min, float max) = 0;
	};
}}