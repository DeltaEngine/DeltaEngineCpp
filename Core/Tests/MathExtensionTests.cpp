#include "CppUnitTest.h"
#include "Core\MathExtensions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	TEST_CLASS(MathExtensionsTests)
	{
	public:
		TEST_METHOD(MathExtensions_Abs)
		{
			Assert::AreEqual(1.67f, MathExtensions::Abs(1.67f));
			Assert::AreEqual(1.67f, MathExtensions::Abs(-1.67f));
		}

		TEST_METHOD(MathExtensions_IsNearlyEqual)
		{
			Assert::IsTrue(MathExtensions::IsNearlyEqual(1.67f, 1.6700001f));
			Assert::IsTrue(MathExtensions::IsNearlyEqual(-1.67f, -1.6700001f));
			Assert::IsFalse(MathExtensions::IsNearlyEqual(-1.67f, -1.678f));
		}

		TEST_METHOD(MathExtensions_Round)
		{
			Assert::AreEqual(2.0f, MathExtensions::Round(1.57f));
			Assert::AreEqual(1.0f, MathExtensions::Round(1.37f));
			Assert::AreEqual(-2.0f, MathExtensions::Round(-1.57f));
			Assert::AreEqual(-1.0f, MathExtensions::Round(-1.37f));
			Assert::AreEqual(1.6f, MathExtensions::Round(1.57f, 1));
			Assert::AreEqual(1.37f, MathExtensions::Round(1.372492f, 2));
			Assert::AreEqual(-1.6f, MathExtensions::Round(-1.57f, 1));
			Assert::AreEqual(-1.37f, MathExtensions::Round(-1.37f, 3));
		}

		TEST_METHOD(MathExtensions_Sin)
		{
			Assert::AreEqual(0.0f, MathExtensions::Sin(0.0f));
			Assert::AreEqual(1.0f, MathExtensions::Sin(90.0f));
			Assert::AreEqual(-1.0f, MathExtensions::Sin(270.0f));
		}

		TEST_METHOD(MathExtensions_Cos)
		{
			Assert::AreEqual(1.0f, MathExtensions::Cos(0.0f));
			Assert::IsTrue(MathExtensions::IsNearlyEqual(0.0f, MathExtensions::Cos(90.0f)));
			Assert::AreEqual(-1.0f, MathExtensions::Cos(180.0f));
		}

		TEST_METHOD(MathExtensions_Lerp)
		{
			Assert::AreEqual(0.5f, MathExtensions::Lerp(0.0f, 1.0f, 0.5f));
			Assert::AreEqual(0.0f, MathExtensions::Lerp(-1.0f, 1.0f, 0.5f));
			Assert::AreEqual(-1.0f, MathExtensions::Lerp(-1.0f, 1.0f, -0.5f));
			Assert::AreEqual(1.0f, MathExtensions::Lerp(-1.0f, 1.0f, 1.25f));
		}

		TEST_METHOD(MathExtensions_Statics)
		{
			Assert::AreEqual(0.0001f, MathExtensions::Epsilon);
			Assert::AreEqual(3.14159265359f, MathExtensions::Pi);
		}
	};
}}}