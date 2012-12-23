#include "CppUnitTest.h"
#include "CppUnitTestCoreSupport.h"
#include "Core\StringHelper.h"
#include "Core\CoreString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	TEST_CLASS(StringHelperTests)
	{
	public:
		TEST_METHOD(StringHelper_Contains)
		{
			Assert::IsFalse(StringHelper::Contains("Hi there", "Hallo"));
			Assert::IsTrue(StringHelper::Contains("Hi there", "Hi"));
			Assert::IsTrue(StringHelper::Contains("Hi there", "he"));
		}

		TEST_METHOD(StringHelper_AreEqual)
		{
			Assert::IsFalse(StringHelper::AreEqual("Hi there", "Hallo"));
			Assert::IsTrue(StringHelper::AreEqual("Hi", String("Hi").ToCharArray()));
		}
	};
}}}