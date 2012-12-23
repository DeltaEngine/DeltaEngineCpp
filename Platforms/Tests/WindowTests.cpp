#include "CppUnitTest.h"
#include "Platforms\Window.h"
#include "TestResolver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Platforms;

namespace DeltaEngine { namespace Platforms { namespace Tests
{
	TEST_CLASS(WindowTests)
	{
	public:
		TEST_METHOD(Window_GetTitle)
		{
			auto resolver = std::make_shared<TestResolver>();
			Assert::AreEqual("MockWindow", resolver->Resolve<Window>()->GetTitle().ToCharArray());
		}
	};
}}}