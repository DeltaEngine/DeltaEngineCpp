#pragma once
#include "Object.h"

namespace DeltaEngine { namespace Core {

	// Wraps and extends the native math functions, but uses floats and provides some extra constants
	class CoreLibrary MathExtensions
	{
	public:
		static const float Pi;
		static const float Epsilon;

		static float Abs(float value);
		static float Round(float value);
		static float Round(float value, int decimalsToRound);
		static bool IsNearlyEqual(float value1, float value2);
		static float Sin(float degreeValue);
		static float Cos(float degreeValue);
		static float Lerp(float value1, float value2, float percentage);
	};
}}