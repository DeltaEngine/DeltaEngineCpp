#pragma once
#include "Core/Runner.h"
#include "Core/IDisposable.h"
#include "Core/List.h"
#include <memory>

namespace DeltaEngine { namespace Core { namespace Tests
{
	class MockWindow : public virtual Runner, public virtual IDisposable
	{
	public:
		MockWindow(std::shared_ptr<List<String>> output)
			: output(output) {}
		~MockWindow() { Dispose(); }
		void Dispose() {}

		void Run()
		{
			output->Add("Window.Run");
		}

	private:
		std::shared_ptr<List<String>> output;
	};
}}}