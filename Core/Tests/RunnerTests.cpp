#include "CppUnitTest.h"
#include "CppUnitTestCoreSupport.h"
#include "Core\Runner.h"
#include "Core\Presenter.h"
#include "Core\List.h"
#include "MockDevice.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	TEST_CLASS(RunnerTests)
	{
	public:
		TEST_METHOD(Runner_Run)
		{
			auto output = std::make_shared<List<String>>();
			auto window = std::make_shared<MockWindow>(output);
			auto device = std::make_shared<MockDevice>(window, output);
			device->Run();
			output->Add("RunnerTests_Run");
			device->Present();
			AreEqual("Window.Run, Device.Run, RunnerTests_Run, Device.Present", output->ToText());
		}
	};
}}}