#pragma once
#include "Core/Runner.h"
#include "Platforms/WindowsOpenGL/App.h"
#include "Rendering/ColoredRectangle.h"
#include <memory>

namespace DeltaEngine { namespace WindowsOpenGL { namespace VisualTests
{
	class AppTests
	{
	public:
		static void ShowWindowAndStartRunner()
		{
			Platforms::App::Start<DummyRunner>([](std::shared_ptr<DummyRunner> dummy){});
		}

		static void ShowColoredRectangle()
		{
			Platforms::App::Start<Rendering::Renderer>([](std::shared_ptr<Rendering::Renderer> r)
			{
				new Rendering::ColoredRectangle(r, Datatypes::Point::Half, Datatypes::Size::Half,
					Datatypes::Color::Red);
			});
		}

	private:
		class DummyRunner : public Core::Runner
		{
		public:
			typedef Hypodermic::AutowiredConstructor<DummyRunner()> AutowiredSignature;

			void Run() {}
		};
	};
}}}