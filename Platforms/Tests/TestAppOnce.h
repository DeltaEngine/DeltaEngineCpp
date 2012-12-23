#pragma once
#include "TestResolver.h"
#include "Core/Exception.h"
#include "Core/Runner.h"

namespace DeltaEngine { namespace Platforms { namespace Tests
{
	class TestAppOnce final
	{
	public:
		template<class AppEntryRunner>
		static void Start()
		{
			static_assert(std::is_convertible<AppEntryRunner, Core::Runner>::value,
				"Must use a type derived from Runner to start app!");
			std::unique_ptr<TestResolver> resolver(new TestResolver());
			resolver->Init<AppEntryRunner>();
			resolver->Run();
		}

		template<class FirstClass>
		static void Start(std::function<void(std::shared_ptr<FirstClass>)> initCode,
			std::function<void()> runCode = nullptr)
		{
			std::unique_ptr<TestResolver> resolver(new TestResolver());
			resolver->Init<FirstClass>(initCode);
			resolver->Run(runCode);
		}

		template<class First, class Second>
		static void Start(std::function<void(std::shared_ptr<First>, std::shared_ptr<Second>)>
			initCode, std::function<void()> runCode = nullptr)
		{
			std::unique_ptr<TestResolver> resolver(new TestResolver());
			resolver->Init<First, Second>(initCode);
			resolver->Run(runCode);
		}

		template<class First, class Second, class Third>
		static void Start(std::function<void(std::shared_ptr<First>, std::shared_ptr<Second>,
			std::shared_ptr<Third>)> initCode, std::function<void()> runCode = nullptr)
		{
			std::unique_ptr<TestResolver> resolver(new TestResolver());
			resolver->Init<First, Second, Third>(initCode);
			resolver->Run(runCode);
		}
	};
}}}