#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "CppUnitTestDatatypesSupport.h"
#include "Datatypes/Rectangle.h"
#include "Datatypes/Point.h"
#include "Datatypes/Size.h"
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Datatypes;
using namespace DeltaEngine::Core;

namespace DeltaEngine { namespace Datatypes { namespace Tests
{
	TEST_CLASS(RectangleTests)
	{
	public:
		TEST_METHOD(Rectangle_DefautProprieties)
		{
			auto emptyRect = Rectangle(0, 0, 0, 0);
			Assert::IsTrue(emptyRect.TopLeft == Point::Zero);
			Assert::IsTrue(emptyRect._Size == Size::Zero);
		}

		TEST_METHOD(Rectangle_Create)
		{
			auto point = Point(2.f, 2.f);
			auto size = Size(1.f, 1.f);
			auto rect = Rectangle(point, size);
			Assert::AreEqual(point, rect.TopLeft);
			Assert::AreEqual(size, rect._Size);
			Assert::AreEqual(point.X, rect.GetLeft());
			Assert::AreEqual(point.Y, rect.GetTop());
			Assert::AreEqual(size.Width, rect.GetWidth());
			Assert::AreEqual(size.Height, rect.GetHeight());
		}

		TEST_METHOD(Rectangle_Properties)
		{
			auto point = Point(2.f, 2.f);
			auto size = Size(1.f, 1.f);
			auto bottomRight = point + Point(size.Width, size.Height);
			auto rect1 = Rectangle(0, 0, 0, 0);
			rect1.SetLeft(point.X);
			rect1.SetTop(point.Y);
			rect1.SetWidth(size.Width);
			rect1.SetHeight(size.Height);
			rect1.SetBottomRight(bottomRight);
			Assert::IsTrue(bottomRight == rect1.GetBottomRight());
			Assert::IsTrue(rect1 == Rectangle(point, size));
		}

		TEST_METHOD(Rectangle_Equals)
		{
			auto rect1 = Rectangle(3, 4, 1, 2);
			auto rect2 = Rectangle(5, 6, 1, 2);
			Assert::IsTrue(rect1 != rect2);
			Assert::IsFalse(rect1 != rect1);
			Assert::AreNotEqual(rect1, rect2);
			Assert::IsTrue(rect1 == Rectangle(3, 4, 1, 2));
			Assert::AreEqual(rect1, Rectangle(3, 4, 1, 2));
		}

		TEST_METHOD(Rectangle_RectangleToString)
		{
			auto rect = Rectangle(2.0f, 2.0f, 1.0f, 1.0f);

			Assert::IsTrue("(2, 2, 1, 1)" == rect.ToString());
		}
		
		TEST_METHOD(Rectangle_RectangleToStringAndFromString)
		{
			auto rect = Rectangle(2.12f, 2.12f, 1.12f, 1.12f);
			String rectString = rect.ToString();
			Assert::IsTrue(rect == Rectangle(rectString));
			Assert::AreEqual(Rectangle::One, Rectangle("(0, 0, 1, 1)"));
			Assert::ExpectException<Rectangle::InvalidNumberOfComponents>([] { Rectangle("abc"); });
		}

		TEST_METHOD(Rectangle_GetRight)
		{
			auto rect = Rectangle(1, 2, 10, 20);
			rect.SetRight(13);
			Assert::AreEqual(3.0f, rect.GetLeft());
			Assert::AreEqual(13.0f, rect.GetRight());
			Assert::AreEqual(10.0f, rect.GetWidth());
		}

		TEST_METHOD(Rectangle_GetBottom)
		{
			auto rect = Rectangle(1, 2, 10, 20);
			rect.SetBottom(23);
			Assert::AreEqual(3.0f, rect.GetTop());
			Assert::AreEqual(23.0f, rect.GetBottom());
			Assert::AreEqual(20.0f, rect.GetHeight());
		}

		TEST_METHOD(Rectangle_GetTopRight)
		{
			auto rect = Rectangle(1, 2, 10, 20);
			rect.SetTopRight(Point(13, 4));
			Assert::AreEqual(3.0f, rect.GetLeft());
			Assert::AreEqual(4.0f, rect.GetTop());
			Assert::AreEqual(10.0f, rect.GetWidth());
			Assert::AreEqual(20.0f, rect.GetHeight());
			Assert::AreEqual(Point(13, 4), rect.GetTopRight());
		}

		TEST_METHOD(Rectangle_GetBottomLeft)
		{
			auto rect = Rectangle(1, 2, 10, 20);
			rect.SetBottomLeft(Point(3, 24));
			Assert::AreEqual(3.0f, rect.GetLeft());
			Assert::AreEqual(4.0f, rect.GetTop());
			Assert::AreEqual(10.0f, rect.GetWidth());
			Assert::AreEqual(20.0f, rect.GetHeight());
			Assert::AreEqual(Point(3, 24), rect.GetBottomLeft());
		}

		TEST_METHOD(Rectangle_GetBottomRight)
		{
			auto rect = Rectangle(1, 2, 10, 20);
			rect.SetBottomRight(Point(13, 24));
			Assert::AreEqual(3.0f, rect.GetLeft());
			Assert::AreEqual(4.0f, rect.GetTop());
			Assert::AreEqual(10.0f, rect.GetWidth());
			Assert::AreEqual(20.0f, rect.GetHeight());
			Assert::AreEqual(Point(13, 24), rect.GetBottomRight());
		}

		TEST_METHOD(Rectangle_GetCenter)
		{
			auto rect = Rectangle(4, 4, 4, 4);
			Assert::AreEqual(Point(4, 4), rect.TopLeft);
			Assert::AreEqual(Point(8, 8), rect.GetBottomRight());
			Assert::AreEqual(Point(6, 6), rect.GetCenter());
		}

		TEST_METHOD(Rectangle_SetCenter)
		{
			auto rect = Rectangle(8, 10, 2, 2);
			rect.SetCenter(Point::One);
			Assert::AreEqual(Point(0, 0), rect.TopLeft);
			Assert::AreEqual(Point(2, 2), rect.GetBottomRight());
			Assert::AreEqual(Point(1, 1), rect.GetCenter());
		}

		TEST_METHOD(Rectangle_Contains)
		{
			auto rect = Rectangle(1, 2, 10, 20);
			Assert::IsTrue(rect.Contains(Point(1, 2)));
			Assert::IsTrue(rect.Contains(Point(5, 5)));
			Assert::IsFalse(rect.Contains(Point(11, 5)));
			Assert::IsFalse(rect.Contains(Point(5, 22)));
		}

		TEST_METHOD(Rectangle_FromCenter)
		{
			Rectangle rect = Rectangle::FromCenter(Point(11, 12), Size(4, 6));
			Assert::AreEqual(Rectangle(9, 9, 4, 6), rect);
		}

		TEST_METHOD(Rectangle_GetAspect)
		{
			Assert::AreEqual(0.5f, Rectangle(0, 0, 1, 2).GetAspect());
			Assert::AreEqual(2.0f, Rectangle(0, 0, 4, 2).GetAspect());
		}

		TEST_METHOD(Rectangle_Statics)
		{
			Assert::AreEqual(Rectangle(0, 0, 0, 0), Rectangle::Zero);
			Assert::AreEqual(Rectangle(0, 0, 1, 1), Rectangle::One);
		}
	};
}}}