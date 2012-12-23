#pragma once
#include "DeltaEngine.Core.h"
#include "DeltaEngine.Datatypes.h"
#include "DeltaEngine.Graphics.h"
#include "DeltaEngine.Platforms.h"
#include "DeltaEngine.Rendering.h"
#include "Hypodermic/AutowiredConstructor.h"

namespace LogoApp
{
	// Displays a colored rectangle in a simple 800x600 window. Will be changed soon to use images!
	class LogoGame : public DeltaEngine::Core::Runner
	{
	public:
		typedef Hypodermic::AutowiredConstructor<LogoGame(DeltaEngine::Rendering::Renderer*,
			DeltaEngine::Core::Time*, DeltaEngine::Platforms::Window*)> AutowiredSignature;
		LogoGame(std::shared_ptr<DeltaEngine::Rendering::Renderer> render,
			std::shared_ptr<DeltaEngine::Core::Time> time,
			std::shared_ptr<DeltaEngine::Platforms::Window> window);
		void Run();

	private:
		std::shared_ptr<DeltaEngine::Rendering::ColoredRectangle> box;
		DeltaEngine::Core::Time* time;
		DeltaEngine::Platforms::Window* window;
		DeltaEngine::Datatypes::Point moveDirection;

		void SetMoveDirectionAndChangeColor(const DeltaEngine::Datatypes::Point& direction);
	};
}