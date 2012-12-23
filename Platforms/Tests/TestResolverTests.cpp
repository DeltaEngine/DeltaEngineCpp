#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "Datatypes/Tests/CppUnitTestDatatypesSupport.h"
#include "TestAppOnce.h"
#include "Graphics/Device.h"
#include "Datatypes/Size.h"
#include "TestResolver.h"
#include "Platforms/Window.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Core;
using namespace DeltaEngine::Datatypes;
using namespace DeltaEngine::Graphics;

namespace DeltaEngine { namespace Platforms { namespace Tests
{
	TEST_CLASS(TestResolverTests)
	{
	public:
		TEST_METHOD(TestResolver_ResolveWindowDeviceAndDrawing)
		{
			std::unique_ptr<TestResolver> resolver(new TestResolver());
			Assert::IsNotNull(resolver->Resolve<Window>().get());
			Assert::IsNotNull(resolver->Resolve<Device>().get());
			Assert::IsNotNull(resolver->Resolve<Drawing>().get());
			Assert::IsTrue(resolver->Resolve<Device>().get() ==
				resolver->Resolve<Drawing>()->GetGraphicsDevice().get());
		}
	};
}}}