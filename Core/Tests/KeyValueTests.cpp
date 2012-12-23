#include "CppUnitTest.h"
#include "Core\KeyValue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	TEST_CLASS(KeyValueTests)
	{
	public:
		TEST_METHOD(KeyValue_Empty)
		{
			auto keyValue = KeyValue();
			Assert::IsTrue(NULL == keyValue.Key);
			Assert::IsTrue(NULL == keyValue.Value);
		}

		TEST_METHOD(KeyValue_Constructor)
		{
			auto obj1 = &Object();
			auto obj2 = &Object();
			auto keyValue = KeyValue(obj1, obj2);
			Assert::IsTrue(obj1 == keyValue.Key);
			Assert::IsTrue(obj2 == keyValue.Value);
		}
	};
}}}