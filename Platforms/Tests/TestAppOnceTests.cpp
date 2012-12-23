#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "Datatypes/Tests/CppUnitTestDatatypesSupport.h"
#include "TestAppOnce.h"
#include "Graphics/Device.h"
#include "Datatypes/Size.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Core;
using namespace DeltaEngine::Datatypes;
using namespace DeltaEngine::Graphics;

namespace DeltaEngine { namespace Platforms { namespace Tests
{
	TEST_CLASS(TestAppOnceTests)
	{
	public:
		TEST_METHOD(TestAppOnce_StartWithRunner)
		{
			TestAppOnce::Start<DummyRunner>();
		}

		TEST_METHOD(TestAppOnce_StartWithOneClass)
		{
			TestAppOnce::Start<DummyRunner>([](std::shared_ptr<DummyRunner> dummy) {}, []() {});
		}

		TEST_METHOD(TestAppOnce_StartWithTwoClasses)
		{
			TestAppOnce::Start<DummyRunner, DummyPresenter>([](std::shared_ptr<DummyRunner> dummy1,
				std::shared_ptr<DummyPresenter> dummy2) {});
		}

		TEST_METHOD(TestAppOnce_StartWithThreeClasses)
		{
			TestAppOnce::Start<DummyRunner, DummyRunner, DummyRunner>([](
				std::shared_ptr<DummyRunner> dummy1, std::shared_ptr<DummyRunner> dummy2,
				std::shared_ptr<DummyRunner> dummy3) {});
		}

		TEST_METHOD(TestAppOnce_StartTwice)
		{
			TestAppOnce::Start<DummyRunner>();
			TestAppOnce::Start<DummyRunner>();
		}

		TEST_METHOD(TestAppOnce_RegisterUnknownClassToMakeResolveSucceed)
		{
			TestAppOnce::Start<ClassWithInnerClass::UnknownInnerClass>(
				[](std::shared_ptr<ClassWithInnerClass::UnknownInnerClass> dummy) {});
		}

		BEGIN_INTEGRATION_TEST(TestAppOnce_CreateWindowAndDevice)
		{
			TestAppOnce::Start<Window, Device>([](std::shared_ptr<Window> window,
				std::shared_ptr<Device> device)
			{
				Assert::IsTrue(window->GetIsVisible());
			});
		}
		END_INTEGRATION_TEST

		BEGIN_INTEGRATION_TEST(TestAppOnce_ResizeWindow)
		{
			TestAppOnce::Start<Window>([](std::shared_ptr<Window> window)
			{
				window->SetTotalSize(Size(800, 600));
				AreEqual(Size(800, 600), window->GetTotalSize());
			});
		}
		END_INTEGRATION_TEST

	private:
		class DummyRunner : public virtual Runner, public virtual IDisposable
		{
		public:
			typedef Hypodermic::AutowiredConstructor<DummyRunner()> AutowiredSignature;

			void Run() {}
			void Dispose() {}
		};

		class DummyPresenter : public virtual Presenter
		{
		public:
			typedef Hypodermic::AutowiredConstructor<DummyPresenter()> AutowiredSignature;

			void Run() {}
			void Present() {}
		};

		class ClassWithInnerClass
		{
		public:
			class UnknownInnerClass
			{
			public:
				typedef Hypodermic::AutowiredConstructor<UnknownInnerClass()> AutowiredSignature;
				virtual ~UnknownInnerClass() {}
			};

			typedef Hypodermic::AutowiredConstructor<ClassWithInnerClass(UnknownInnerClass*)>
				AutowiredSignature;

			ClassWithInnerClass(std::shared_ptr<UnknownInnerClass> inner)
			{
				Assert::IsNotNull(inner.get());
			}
			virtual ~ClassWithInnerClass() {}
		};
	};
}}}