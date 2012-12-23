#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "Platforms/WindowsOpenGL/OpenGLResolver.h"
#include "Platforms/Windows/Win32Window.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Core;
using namespace DeltaEngine::Graphics;
using namespace DeltaEngine::Platforms;
using namespace DeltaEngine::Platforms::Windows;
using namespace DeltaEngine::Rendering;

namespace DeltaEngine { namespace WindowsOpenGL { namespace VisualTests
{
	TEST_CLASS(OpenGLResolverTests)
	{
	public:
		OpenGLResolverTests()
			: resolver(Platforms::OpenGLResolver()) {}

		BEGIN_INTEGRATION_TEST(OpenGLResolver_MakeSureAllTypesCanBeResolved)
		{
			MakeSureTypeCanBeResolved<Time>("Time");
			MakeSureTypeCanBeResolved<ElapsedTime>("StopwatchTime");
			MakeSureTypeCanBeResolved<Window>("OpenGLWindow");
			MakeSureTypeCanBeResolved<Device>("OpenGLDevice");
			MakeSureTypeCanBeResolved<Renderer>("Renderer");
			auto notRegisteredClass = resolver.Resolve<OpenGLResolverTests>();
			Assert::IsNull(notRegisteredClass.get());
		}
		END_INTEGRATION_TEST

	private:
		Platforms::OpenGLResolver resolver;

		template<class Type>
		void MakeSureTypeCanBeResolved(const char* expectedClassName)
		{
			auto instance = resolver.Resolve<Type>();
			Assert::IsNotNull(instance.get(), String::Format("MakeSureTypeCanBeResolved failed for %s",
				typeid(Type).name()).ToWString().c_str());
			Contains(instance->ToString(), expectedClassName);
			instance.reset();
		}
	};
}}}