#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "Core/Resolver.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Core;

namespace DeltaEngine { namespace Platforms { namespace Tests
{
	// Provides test classes and a configuration for the RunnersAreExecutedInCorrectOrder test.
	TEST_CLASS(AppRunnerTests)
	{
	public:
		TEST_METHOD(AppRunner_RunnersAreExecutedInCorrectOrder)
		{
			auto resolver = std::make_shared<TestResolver>();
			resolver->Run();

			String ExpectedOutput = "Window.Run, Device.Run, AppRunnerTests, Device.Present";
			Assert::AreEqual(ExpectedOutput, Output.ToText());
		}

		TEST_METHOD(AppRunner_EmptyConfigurationShouldNotCrash)
		{
			auto resolver = std::make_shared<TestResolver>();
			resolver->Dispose();
		}

	private:
		static List<String> Output;

		class TestResolver : public Resolver
		{
		public:
			TestResolver()
			{
				RegisterInstance(std::make_shared<Window>());
				RegisterInstance(std::make_shared<Device>());
			}

			void Run()
			{
				RunAllRunners();
				Output.Add("AppRunnerTests");
				RunAllPresenters();
			}

			template <typename Type>
			std::shared_ptr<Type> Resolve()
			{
				return default(BaseType);
			}

		private:
			void RegisterInstance(std::shared_ptr<Object> instance)
			{
				RegisterInstanceAsRunnerOrPresenterIfPossible(instance);
			}
		};

		class Device : public virtual Presenter
		{
		public:
			void Run()
			{
				Output.Add("Device.Run");
			}

			void Present()
			{
				Output.Add("Device.Present");
			}
		};

		class Window : public virtual Runner
		{
		public:
			void Run()
			{
				Output.Add("Window.Run");
			}
		};
	};

	List<String> AppRunnerTests::Output = List<String>();
}}}