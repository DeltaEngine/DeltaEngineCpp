#include "CppUnitTest.h"
#include "CppUnitTestCoreSupport.h"
#include "Core\CoreString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	class DerivedObject : public virtual Object
	{
	public:
		DerivedObject(int foo = 0)
		{
			this->foo = foo;
		}

		virtual unsigned int GetHashCode()
		{
			return foo;
		}

	private:
		int foo;
	};

	TEST_CLASS(ObjectTests)
	{
	public:
		TEST_METHOD(Object_ToString)
		{
			auto obj = Object();
			AreEqual("class DeltaEngine::Core::Object", obj.ToString());
		}

		TEST_METHOD(Object_GetHashCode)
		{
			auto obj = Object();
			Assert::AreEqual(3646367871U, obj.GetHashCode());
		}

		TEST_METHOD(DerivedObject_ToString)
		{
			auto obj = &DerivedObject();
			String s = obj->ToString();
			AreEqual("class DeltaEngine::Core::Tests::DerivedObject", obj->ToString());
		}

		TEST_METHOD(DerivedObject_GetHashCode)
		{
			auto obj = DerivedObject(27);
			Assert::AreEqual(27U, obj.GetHashCode());
		}
	};
}}}