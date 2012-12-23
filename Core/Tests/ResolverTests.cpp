#include "CppUnitTest.h"
#include "CppUnitTestCoreSupport.h"
#include "Core\Resolver.h"
#include "Core\List.h"
#include "MockDevice.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	TEST_CLASS(ResolverTests)
	{
	public:
		class MockResolver : public Resolver
		{
		public:
			MockResolver()
				: registeredInstances() {}

			void RegisterInstance(std::shared_ptr<Object> instance)
			{
				registeredInstances.Add(instance);
				RegisterInstanceAsRunnerOrPresenterIfPossible(instance);
			}

			template<class BaseType>
			std::shared_ptr<BaseType> Resolve()
			{
				for (auto instance : registeredInstances)
				{
					auto castedInstance = std::dynamic_pointer_cast<BaseType>(instance);
					if (castedInstance != NULL)
						return castedInstance;
				}

				return NULL;
			}

			List<std::shared_ptr<Object>> registeredInstances;
		};

		TEST_METHOD(Resolver_Run)
		{
			auto output = std::make_shared<List<String>>();
			auto resolver = MockResolver();
			auto window = std::make_shared<MockWindow>(output);
			resolver.RegisterInstance(window);
			auto device = std::make_shared<MockDevice>(window, output);
			resolver.RegisterInstance(device);
			Assert::IsTrue(window == resolver.Resolve<MockWindow>());
			Assert::IsTrue(device == resolver.Resolve<MockDevice>());
			Assert::IsNull(resolver.Resolve<Resolver>().get());

			resolver.RunAllRunners();
			resolver.RunAllPresenters();
			output->Add("Finished");
			AreEqual("Window.Run, Window.Run, Device.Run, Device.Present, Finished", output->ToText());
		}

		TEST_METHOD(Resolver_DisposeTwice)
		{
			auto resolver = MockResolver();
			resolver.Dispose();
			resolver.Dispose();
		}
	};
}}}