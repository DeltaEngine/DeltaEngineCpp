#pragma once
#include "Core/Presenter.h"
#include "MockWindow.h"
#include <memory>

namespace DeltaEngine { namespace Core { namespace Tests
{
	class MockDevice : public virtual Presenter
	{
	public:
		MockDevice(std::shared_ptr<MockWindow> window, std::shared_ptr<List<String>> output)
			: window(window), output(output) {}

		void Run()
		{
			window->Run();
			output->Add("Device.Run");
		}

		void Present()
		{
			output->Add("Device.Present");
		}

	private:
		std::shared_ptr<MockWindow> window;
		std::shared_ptr<List<String>> output;
	};
}}}