#include "CppUnitTest.h"
#include "Datatypes\Tests\CppUnitTestDatatypesSupport.h"
#include "Rendering\Renderer.h"
#include "Rendering\ColoredRectangle.h"
#include "Graphics\Tests\MockDrawing.h"
#include "Graphics\Tests\MockDevice.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Datatypes;
using namespace DeltaEngine::Graphics::Tests;
using namespace DeltaEngine::Rendering;

TEST_CLASS(ColoredRectangleTests)
{
public:
	ColoredRectangleTests()
	{
		surface = std::make_shared<MockDrawing>(std::make_shared<MockDevice>());
		rect = Rectangle(0, 0, 5, 5);
		renderer = std::make_shared<Renderer>(surface);
		whiteRect = std::make_shared<ColoredRectangle>(renderer, rect, Color::White);
	}

	~ColoredRectangleTests()
	{
		renderer->Dispose();
	}

	TEST_METHOD(ColoredRectangle_Create)
	{
		Assert::AreEqual(1, renderer->GetNumberOfVisibles());
		auto newColoredRect = std::make_shared<ColoredRectangle>(renderer, Point::Zero, Size::One,
			Color::White);
		Assert::AreEqual(2, renderer->GetNumberOfVisibles());
	}

	TEST_METHOD(ColoredRectangle_Fields)
	{
		Assert::AreEqual(whiteRect->Color, Color::White);
		Assert::AreEqual(whiteRect->Rect, rect);
	}

	TEST_METHOD(ColoredRectangle_Render)
	{
		whiteRect->Render();

		Assert::AreEqual("(R=255, G=255, B=255, A=255), (0, 0, 5, 5)",
			surface->GetResult().ToCharArray());
	}

private:
	std::shared_ptr<ColoredRectangle> whiteRect;
	std::shared_ptr<MockDrawing> surface;
	std::shared_ptr<Renderer> renderer;
	Rectangle rect;
};