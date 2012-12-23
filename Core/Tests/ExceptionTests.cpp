#include "CppUnitTest.h"
#include "CppUnitTestCoreSupport.h"
#include "Core/Exception.h"
#include "Core/CoreString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	class CustomException : public Exception
	{
	public:
		virtual String ToString() const
		{
			return "CustomException";
		}
	};

	TEST_CLASS(ExceptionTests)
	{
	public:
		TEST_METHOD(Exception_Constructor)
		{
			auto testException = Exception(String("TestException"));
			Assert::AreEqual("TestException", testException.what());
			Contains(testException.ToString(), "TestException");
		}

		TEST_METHOD(Exception_Throw)
		{
			try
			{
				throw Exception("TestException");
			}
			catch (Exception& ex)
			{
				Contains(ex.what(), "TestException");
			}
		}

#if _DEBUG
		BEGIN_INTEGRATION_TEST(Exception_ThrowWithStacktrace)
		{
			try
			{
				throw Exception("TestException");
			}
			catch (Exception& ex)
			{
				Contains(ex.ToString(), ": DeltaEngine::Core::Tests::ExceptionTests::Exception_Throw");
			}
		}
		END_INTEGRATION_TEST
#endif

		TEST_METHOD(Exception_ThrowCustomException)
		{
			try
			{
				throw CustomException();
			}
			catch (Exception& ex)
			{
				Contains(ex.ToString(), "CustomException");
			}
		}
	};
}}}