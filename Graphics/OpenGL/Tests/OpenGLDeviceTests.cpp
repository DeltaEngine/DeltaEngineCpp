#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "Datatypes/Tests/CppUnitTestDatatypesSupport.h"
#include "Platforms/WindowsOpenGL/App.h"
#include "Graphics/OpenGL/OpenGLDrawing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Datatypes;
using namespace DeltaEngine::Platforms;

namespace DeltaEngine { namespace Graphics { namespace OpenGL { namespace Tests
{
	TEST_CLASS(OpenGLDeviceTests)
	{
	public:
		BEGIN_INTEGRATION_TEST(OpenGLDevice_Dispose)
		{
			App::Start<Device>([](std::shared_ptr<Device> device)
			{
				device->Dispose();
			});
		}
		END_INTEGRATION_TEST

		BEGIN_INTEGRATION_TEST(OpenGLDevice_RunWithBackgroundColor)
		{
			App::Start<Device, Window>([](std::shared_ptr<Device> device, std::shared_ptr<Window> window)
			{
				window->SetBackgroundColor(Color::Red);
				device->Dispose();
			});
		}
		END_INTEGRATION_TEST

		BEGIN_INTEGRATION_TEST(OpenGLDevice_Present)
		{
			App::Start<Device>([](std::shared_ptr<Device> device)
			{
				device->Present();
				device->Dispose();
			});
		}
		END_INTEGRATION_TEST

		BEGIN_INTEGRATION_TEST(OpenGLDevice_SizeChanged)
		{
			App::Start<Device, Window>([](std::shared_ptr<Device> device, std::shared_ptr<Window> window)
			{
				window->SetTotalSize(Size(100, 100));
			});
		}
		END_INTEGRATION_TEST
	};
}}}}