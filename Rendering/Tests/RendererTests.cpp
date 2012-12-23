#include "CppUnitTest.h"
#include "MockRenderable.h"
#include "Rendering/Renderer.h"
#include "Graphics/Tests/MockDrawing.h"
#include "Graphics/Tests/MockDevice.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Graphics::Tests;
using namespace DeltaEngine::Rendering::Tests;
using namespace DeltaEngine::Rendering;

TEST_CLASS(RendererTests)
{
public:
	TEST_METHOD(Renderer_NumRenders)
	{
		auto draw = std::make_shared<MockDrawing>(std::make_shared<MockDevice>());
		auto renderer = std::make_shared<Renderer>(draw);
		auto first = std::make_shared<MockRenderable>(renderer);
		auto second = std::make_shared<MockRenderable>(renderer);
		
		IsNumRenders(renderer, 2);
		first->Dispose();
		IsNumRenders(renderer, 1);
	}

private:
	void IsNumRenders(std::shared_ptr<Renderer> renderer, int expected)
	{
		MockRenderable::NumRenders = 0;
		renderer->Run();

		Assert::AreEqual(expected, MockRenderable::NumRenders);
	}
};