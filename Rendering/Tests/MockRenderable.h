#pragma once
#include "Rendering/Renderable.h"

namespace DeltaEngine {namespace Rendering { namespace Tests
{
	class MockRenderable : public Renderable
	{
	public:
		MockRenderable(std::shared_ptr<Renderer> renderer)
			: Renderable(renderer) {}

		virtual void Render();
		static int NumRenders;
	};
}}}