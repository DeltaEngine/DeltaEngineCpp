#include "Core/CoreString.h"
#include "Core/Resolver.h"
#include <memory>

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework
{
	// http://blogs.msdn.com/b/visualstudioalm/archive/2012/11/09/how-to-manage-unit-tests-in-visual-studio-2012-update-1-part-1-using-traits-in-the-unit-test-explorer.aspx
	// These macros can be used to simplify how to write integration tests that automatically quit.
#define BEGIN_INTEGRATION_TEST(methodName)\
	BEGIN_TEST_METHOD_ATTRIBUTE(methodName)\
	TEST_METHOD_ATTRIBUTE(L"Category", L"Slow")\
	END_TEST_METHOD_ATTRIBUTE()\
	TEST_METHOD(methodName)\
	{\
		DeltaEngine::Core::Resolver::CurrentlyInAutomatedUnitTest = false;\
		DeltaEngine::Core::Resolver::CurrentlyInIntegrationTest = true;

#define END_INTEGRATION_TEST\
		DeltaEngine::Core::Resolver::CurrentlyInAutomatedUnitTest = true;\
		DeltaEngine::Core::Resolver::CurrentlyInIntegrationTest = false;\
	}
	
	template<> static std::wstring ToString<unsigned short>(const unsigned short& t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<> static std::wstring ToString<long long>(const long long& t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<> static std::wstring ToString<DeltaEngine::Core::String>(
		const DeltaEngine::Core::String& t)
	{
		return t.ToString().ToWString();
	}

	template<> static std::wstring ToString<DeltaEngine::Core::Object>(
		const DeltaEngine::Core::Object* t)
	{
		if (t == NULL)
			return std::wstring(L"(NULL)");

		return t->ToString().ToWString();
	}

	template<> static std::wstring ToString<DeltaEngine::Core::Object>(DeltaEngine::Core::Object* t)
	{
		if (t == NULL)
			return std::wstring(L"(NULL)");

		return t->ToString().ToWString();
	}

	static void AreEqual(const char* expected, const DeltaEngine::Core::String& actual)
	{
		Assert::AreEqual(expected, actual.ToCharArray());
	}

	static void AreEqual(const DeltaEngine::Core::String& expected, const char* actual)
	{
		Assert::AreEqual(expected.ToCharArray(), actual);
	}

	static void AreEqual(const DeltaEngine::Core::String& expected,
		const DeltaEngine::Core::String& actual)
	{
		Assert::AreEqual(expected, actual);
	}

	static void AreEqual(const DeltaEngine::Core::Object* expected,
		const DeltaEngine::Core::Object* actual)
	{
		Assert::IsTrue(expected == actual,
			(expected->ToString() + " is not equal to " + actual->ToString()).ToWString().c_str());
	}

	static void AreEqual(const std::shared_ptr<DeltaEngine::Core::Object> expected,
		const std::shared_ptr<DeltaEngine::Core::Object> actual)
	{
		Assert::IsTrue(expected == actual,
			(expected->ToString() + " is not equal to "+ actual->ToString()).ToWString().c_str());
	}

	static void Contains(const DeltaEngine::Core::String& text, const char* expectedInText)
	{
		Assert::IsTrue(text.Contains(expectedInText),
			(text + " does not contain: "+ expectedInText).ToWString().c_str());
	}
}}}