#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "Core/Time.h"
#include "Graphics/Device.h"
#include "DeltaEngine.Platforms.Windows.h"
#include <windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Core;
using namespace DeltaEngine::Graphics;

namespace DeltaEngine { namespace Platforms { namespace Windows { namespace Tests
{
	// WindowsResolver constructor is protected, we need to derive to create a resolver instance.
	class TestResolver : public WindowsResolver
	{
	public:
		TestResolver() {}
	};

	TEST_CLASS(WindowsResolverTests)
	{
	public:
		BEGIN_INTEGRATION_TEST(WindowsResolver_ResolveWindow)
		{
			auto windowsResolver = std::make_shared<TestResolver>();
			auto window = windowsResolver->Resolve<Window>();
			Assert::IsNotNull(windowsResolver.get());
			Assert::IsNotNull(window.get());
			Contains(window.get()->ToString(), "Win32Window");
			window->Close();
		}
		END_INTEGRATION_TEST

		BEGIN_INTEGRATION_TEST(WindowsResolver_ResolveTime)
		{
			auto windowsResolver = std::make_shared<TestResolver>();

			auto stopwatchTime = windowsResolver->Resolve<StopwatchTime>();
			Assert::IsNotNull(stopwatchTime.get());

			auto elapsedTime = windowsResolver->Resolve<ElapsedTime>();
			Assert::IsNotNull(elapsedTime.get());

			auto time = windowsResolver->Resolve<Time>();
			Assert::IsNotNull(time.get());
		}
		END_INTEGRATION_TEST
	};
}}}}