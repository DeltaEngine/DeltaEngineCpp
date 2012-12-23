#pragma once
#include "Hypodermic/ContainerBuilder.h"
#include "Hypodermic/IContainer.h"
#include "Core/Resolver.h"
#include "Window.h"
#include "Core/CoreString.h"
#include "Core/List.h"
#include <type_traits>

namespace DeltaEngine { namespace Platforms
{
	// Each platform registers its concrete types (e.g. graphics). All types derived from Runner or
	// Presenter are automatically run. Hypodermic details: http://code.google.com/p/hypodermic/
	class HypodermicResolver : public Core::Resolver
	{
	public:
		HypodermicResolver()
			: alreadyRegisteredTypes()
		{
			Resolver::CurrentlyInAutomatedUnitTest = false;
			builder = Hypodermic::ContainerBuilder();
		}

		~HypodermicResolver() { Dispose(); }
		
		virtual void Dispose()
		{
			Core::Resolver::Dispose();
			container.reset();
		}

		template <class AppEntryRunner>
		void Init()
		{
			Resolve<AppEntryRunner>();
		}

		template <class FirstClass>
		void Init(std::function<void(std::shared_ptr<FirstClass>)> initCode)
		{
			AutowireSingletonAsSelf<FirstClass>();
			initCode(Resolve<FirstClass>());
		}

		template <class FirstClass, class SecondClass>
		void Init(std::function<void(std::shared_ptr<FirstClass>, std::shared_ptr<SecondClass>)>
			initCode)
		{
			AutowireSingletonAsSelf<FirstClass>();
			AutowireSingletonAsSelf<SecondClass>();
			initCode(Resolve<FirstClass>(), Resolve<SecondClass>());
		}

		template <class FirstClass, class SecondClass, class ThirdClass>
		void Init(std::function<void(std::shared_ptr<FirstClass>, std::shared_ptr<SecondClass>,
			std::shared_ptr<ThirdClass>)> initCode)
		{
			AutowireSingletonAsSelf<FirstClass>();
			AutowireSingletonAsSelf<SecondClass>();
			AutowireSingletonAsSelf<ThirdClass>();
			initCode(Resolve<FirstClass>(), Resolve<SecondClass>(), Resolve<ThirdClass>());
		}

		virtual void Run(std::function<void()> runCode = nullptr)
		{
			auto window = Resolve<Window>();
			do
				ExecuteRunnersLoopAndPresenters(runCode);
			while (!window->GetIsClosing());
		}

		template <typename Type>
		void Register()
		{
			if (std::is_abstract<Type>::value)
				return;

			auto typeName = Core::String(typeid(Type).name());
			if (alreadyRegisteredTypes.Contains(typeName))
				return;
			alreadyRegisteredTypes.Add(typeName);

			builder.registerType<Type>()->asSelf()->onActivating(ActivatingInstance<Type>());
		}

		template <typename Type>
		typename std::enable_if<!std::is_abstract<Type>::value>::type AutowireSingletonAsSelf()
		{
			alreadyRegisteredTypes.Add(typeid(Type).name());
			builder.autowireType<Type>()->asSelf()->singleInstance()->onActivating(
				ActivatingInstance<Type>());
		}

		template <class Type>
		typename std::enable_if<std::is_abstract<Type>::value>::type AutowireSingletonAsSelf() {}

		template <typename Type, class Interface>
		void AutowireSingleton()
		{
			static_assert(std::is_convertible<Type, Interface>::value,
				"Type must derive from Interface!");
			alreadyRegisteredTypes.Add(typeid(Type).name());
			builder.autowireType<Type>()->as<Interface>()->asSelf()->singleInstance()->onActivating(
				ActivatingInstance<Type>());
		}

		template <typename Type>
		void RegisterSingleton()
		{
			alreadyRegisteredTypes.Add(typeid(Type).name());
			builder.registerType<Type>()->asSelf()->singleInstance()->onActivating(
				ActivatingInstance<Type>());
		}

		template <typename Type>
		void RegisterSingleton(std::function<Type*(Hypodermic::IComponentContext&)>
			constructorDelegate)
		{
			alreadyRegisteredTypes.Add(typeid(Type).name());
			builder.registerType<Type>(constructorDelegate)->asSelf()->singleInstance()->onActivating(
				ActivatingInstance<Type>());
		}

		template <typename Type, class Interface>
		void RegisterSingleton()
		{
			static_assert(std::is_convertible<Type, Interface>::value,
				"Type must derive from Interface!");
			alreadyRegisteredTypes.Add(typeid(Type).name());
			builder.registerType<Type>()->as<Interface>()->asSelf()->singleInstance()->onActivating(
				ActivatingInstance<Type>());
		}

		template <typename Type, class Interface>
		void RegisterSingleton(std::function<Type*(Hypodermic::IComponentContext&)>
			constructorDelegate)
		{
			static_assert(std::is_convertible<Type, Interface>::value,
				"Type must derive from Interface!");
			alreadyRegisteredTypes.Add(typeid(Type).name());
			builder.registerType<Type>(constructorDelegate)->as<Interface>()->asSelf()->
				singleInstance()->onActivating(ActivatingInstance<Type>());
		}

		template <typename Type, class Interface>
		void RegisterInstance(std::shared_ptr<Type> instance)
		{
			static_assert(std::is_convertible<Type, Interface>::value,
				"Type must derive from Interface!");
			alreadyRegisteredTypes.Add(typeid(Type).name());
			builder.registerInstance(instance)->as<Interface>()->asSelf()->onActivating(
				ActivatingInstance<Type>());
		}

		template <typename Type, class Interface>
		std::shared_ptr<Type> RegisterSingletonMock(std::shared_ptr<Type> instance)
		{
			alreadyRegisteredTypes.Add(typeid(Type).name());
			builder.registerInstance(instance)->as<Interface>()->asSelf()->
				singleInstance()->onActivating(ActivatingInstance<Type>());
			return instance;
		}

		template <typename Type>
		std::shared_ptr<Type> Resolve()
		{
			MakeSureContainerIsInitialized();
			return container->resolve<Type>();
		}

	protected:
		Core::List<Core::String> alreadyRegisteredTypes;
		Hypodermic::ContainerBuilder builder;
		std::shared_ptr<Hypodermic::IContainer> container;

		void ExecuteRunnersLoopAndPresenters(std::function<void()> runCode)
		{
			RunAllRunners();

			if (runCode != nullptr)
				runCode();

			RunAllPresenters();
		}

		bool GetIsAlreadyInitialized() { return container != NULL; }

		virtual void MakeSureContainerIsInitialized()
		{
			if (container != NULL)
				return;

			container = builder.build();
		}

	private:
		template<typename T>
		std::function<void(Hypodermic::IActivatingData<T>&)> ActivatingInstance()
		{
			return [&](Hypodermic::IActivatingData<T>& activatingData)
			{
				AddRunnerAndPresenter(activatingData);
			};
		}

		template<typename T>
		void AddRunnerAndPresenter(Hypodermic::IActivatingData<T>& activatingData)
		{
			std::shared_ptr<T> instance = activatingData.instance();
			auto runner = std::dynamic_pointer_cast<Core::Runner>(instance);
			if (runner != NULL)
				runners.Add(runner);

			auto presenter = std::dynamic_pointer_cast<Core::Presenter>(instance);
			if (presenter != NULL)
				presenters.Add(presenter);
		}
	};
}}