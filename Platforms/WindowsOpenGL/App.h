#pragma once
#include "OpenGLResolver.h"

namespace DeltaEngine { namespace Platforms
{
	class App final
	{
	public:
		template<class AppEntryRunner>
		static void Start()
		{
			std::unique_ptr<OpenGLResolver> resolver(new OpenGLResolver());
			resolver->AutowireSingletonAsSelf<AppEntryRunner>();
			resolver->Init<AppEntryRunner>();
			resolver->Run();
		}

		template<class AppEntryRunner>
		static void SetupAndStart(std::function<AppEntryRunner*(Hypodermic::IComponentContext&)>
			constructorRunner)
		{
			std::unique_ptr<OpenGLResolver> resolver(new OpenGLResolver());
			resolver->AutowireSingletonAsSelf<AppEntryRunner>(constructorRunner);
			resolver->Init<AppEntryRunner>();
			resolver->Run();
		}

		template<class FirstClass>
		static void Start(std::function<void(std::shared_ptr<FirstClass>)> initCode,
			std::function<void()> runCode = nullptr)
		{
			std::unique_ptr<OpenGLResolver> resolver(new OpenGLResolver());
			resolver->Init<FirstClass>(initCode);
			resolver->Run(runCode);
		}

		template<class First, class Second>
		static void Start(
			std::function<void(std::shared_ptr<First>, std::shared_ptr<Second>)> initCode,
			std::function<void()> runCode = nullptr)
		{
			std::unique_ptr<OpenGLResolver> resolver(new OpenGLResolver());
			resolver->Init<First, Second>(initCode);
			resolver->Run(runCode);
		}

		template<class First, class Second, class Third>
		static void Start(std::function<void(std::shared_ptr<First>, std::shared_ptr<Second>,
			std::shared_ptr<Third>)> initCode, std::function<void()> runCode = nullptr)
		{
			std::unique_ptr<OpenGLResolver> resolver(new OpenGLResolver());
			resolver->Init<First, Second, Third>(initCode);
			resolver->Run(runCode);
		}
	};
}}