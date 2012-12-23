#pragma once
#include "Object.h"
#include "Randomizer.h"

namespace DeltaEngine { namespace Core
{
	// Returns an integer greater than or equal to min and strictly less than max
	class CoreLibrary PseudoRandom : public virtual Object, public virtual Randomizer
	{
	public:
		PseudoRandom();
		int Get(int min, int max);
		float Get(float min, float max);

	private:
		double GetNextDouble();
		void InitializeSeed();
		unsigned int GetUint();

		long seed;
		unsigned int w;
		unsigned int z;
	};
}}