#include "CppUnitTest.h"
#include "Core\PseudoRandom.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	TEST_CLASS(PseudoRandomTests)
	{
	public:
		TEST_METHOD(PseudoRandom_IntSanityTest)
		{
			auto random = PseudoRandom();
			const int Max = 10;
			auto wasChosen = new bool[Max];
			const int Trials = Max * 1000;
			for (int i = 0; i < Trials; i++)
				wasChosen[random.Get(0, Max)] = true;

			for (int i = 0; i < Max; i++)
				Assert::IsTrue(wasChosen[i]);
			delete wasChosen;
		}

		TEST_METHOD(PseudoRandom_FloatSanityTest)
		{
			auto random = PseudoRandom();
			const int Max = 10;
			auto wasChosen = new bool[(int)Max];
			const int Trials = Max * 1000;
			for (int i = 0; i < Trials; i++)
				wasChosen[(int)random.Get(0.0f, (float)Max)] = true;

			for (int i = 0; i < Max; i++)
				Assert::IsTrue(wasChosen[i]);
			delete wasChosen;
		}
	};
}}}