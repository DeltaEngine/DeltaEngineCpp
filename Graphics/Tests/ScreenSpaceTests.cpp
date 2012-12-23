#include "CppUnitTest.h"
#include "Datatypes/Tests/CppUnitTestDatatypesSupport.h"
#include "Graphics/ScreenSpace.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Graphics;
using namespace DeltaEngine::Datatypes;

namespace DeltaEngine { namespace Graphics { namespace Tests
{
	TEST_CLASS(ScreenSpaceTests)
	{
	public:
		TEST_METHOD(ScreenSpace_ToQuadraticWithSquareWindow)
		{
			auto screen = ScreenSpace(Size(100, 100));
			Assert::AreEqual(Size(100, 100), screen.GetViewportPixelSize());
			Assert::AreEqual(Point::Zero, screen.GetTopLeft());
			Assert::AreEqual(Point::One, screen.GetBottomRight());
			Assert::AreEqual(Size::One, screen.GetArea());
			Assert::AreEqual(Rectangle::One, screen.GetViewport());
			Assert::AreEqual(Point::One, screen.ToQuadraticSpace(Point(100, 100)));
			Assert::AreEqual(Point::Half, screen.ToQuadraticSpace(Point(50, 50)));
			Assert::AreEqual(Rectangle(0.1f, 0.1f, 0.8f, 0.8f),
				screen.ToQuadraticSpace(Rectangle(10, 10, 80, 80)));
		}

		TEST_METHOD(ScreenSpace_ToQuadraticWithNonSquareWindow)
		{
			auto screen = ScreenSpace(Size(100, 75));
			Assert::AreEqual(Point(0, 0.125f), screen.GetTopLeft());
			Assert::AreEqual(Point(1, 0.875f), screen.GetBottomRight());
			Assert::AreEqual(Size(1, 0.75f), screen.GetArea());
			Assert::AreEqual(Rectangle(0, 0.125f, 1, 0.75f), screen.GetViewport());
			Assert::AreEqual(Point(1.0f, 0.875f), screen.ToQuadraticSpace(Point(100, 75)));
			Assert::AreEqual(Point::Half, screen.ToQuadraticSpace(Point(50, 37.5f)));
			Assert::AreEqual(Size(0.1f, 0.1f), screen.ToQuadraticSpace(Size(10, 10)));
		}

		TEST_METHOD(ScreenSpace_ToQuadraticWithPortraitWindow)
		{
			auto screen = ScreenSpace(Size(75, 100));
			Assert::AreEqual(Point(0.125f, 0), screen.GetTopLeft());
			Assert::AreEqual(Point(0.875f, 1), screen.GetBottomRight());
			Assert::AreEqual(Size(0.75f, 1), screen.GetArea());
			Assert::AreEqual(Rectangle(0.125f, 0, 0.75f, 1), screen.GetViewport());
			Assert::AreEqual(Point(0.875f, 1.0f), screen.ToQuadraticSpace(Point(75, 100)));
			Assert::AreEqual(Point::Half, screen.ToQuadraticSpace(Point(37.5f, 50)));
			Assert::AreEqual(Size(0.1f, 0.1f), screen.ToQuadraticSpace(Size(10, 10)));
		}

		TEST_METHOD(ScreenSpace_ToPixelWithSquareWindow)
		{
			auto screen = ScreenSpace(Size(100, 100));
			Assert::AreEqual(Point(100, 100), screen.ToPixelSpace(Point::One));
			Assert::AreEqual(Point::Zero, screen.ToPixelSpace(Point::Zero));
			Assert::AreEqual(Point(50, 50), screen.ToPixelSpace(Point::Half));
		}

		TEST_METHOD(ScreenSpace_ToPixelWithNonSquareWindow)
		{
			auto screen = ScreenSpace(Size(100, 75));
			Assert::AreEqual(Point(100, 75), screen.ToPixelSpace(Point(1.0f, 0.875f)));
			Assert::AreEqual(Point::Zero, screen.ToPixelSpace(Point(0, 0.125f)));
			Assert::AreEqual(Point(50, 37.5f), screen.ToPixelSpace(Point::Half));
			Assert::AreEqual(Size(10, 20), screen.ToPixelSpace(Size(0.1f, 0.2f)));
			Assert::AreEqual(Rectangle(20, 7.5f, 60, 60),
				 screen.ToPixelSpace(Rectangle(0.2f, 0.2f, 0.6f, 0.6f)));
		}

		TEST_METHOD(ScreenSpace_ToPixelWithPortraitWindow)
		{
			auto screen = ScreenSpace(Size(75, 100));
			Assert::AreEqual(Point(75, 100), screen.ToPixelSpace(Point(0.875f, 1.0f)));
			Assert::AreEqual(Point::Zero, screen.ToPixelSpace(Point(0.125f, 0)));
			Assert::AreEqual(Point(37.5f, 50), screen.ToPixelSpace(Point::Half));
			Assert::AreEqual(Size(10, 20), screen.ToPixelSpace(Size(0.1f, 0.2f)));
		}
	};
}}}