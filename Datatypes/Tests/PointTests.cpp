#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "CppUnitTestDatatypesSupport.h"
#include "Datatypes/Point.h"
#include "Datatypes/Size.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Datatypes;
using namespace DeltaEngine::Core;

namespace DeltaEngine { namespace Datatypes { namespace Tests
{
	TEST_CLASS(PointTests)
	{
	public:
		TEST_METHOD(Point_BehavesAsValueType)
		{
			auto p1 = Point(1, 2);
			auto p2 = p1;
			p2.X = 5;		
			Assert::AreEqual(p1.X, 1.f);
		}

		TEST_METHOD(Point_Create)
		{
			float x = 3.51f;
			float y = 0.23f;
			auto point = Point(x, y);
			Assert::AreEqual(point.X, x);
			Assert::AreEqual(point.Y, y);
		}

		TEST_METHOD(Point_Equals)
		{
			auto p1 = Point(1, 2);
			auto p2 = Point(3, 4);
			auto p3 = Point(1, 2);
			Assert::IsTrue(p1 != p2);
			Assert::IsFalse(p1 != p3);
			Assert::IsTrue(p1 == p3);
			Assert::IsFalse(p1 == p2);
			Assert::IsTrue(p1.Equals(p3));
		}

		TEST_METHOD(Point_PlusOperator)
		{
			auto p1 = Point(1, 2);
			auto p2 = Point(3, 4);
			Assert::AreEqual(Point(4, 6), p1 + p2);
		}

		TEST_METHOD(Point_MinusOperator)
		{
			auto p1 = Point(1, 2);
			auto p2 = Point(3, 4);
			Assert::AreEqual(Point(-2, -2), p1 - p2);
		}

		TEST_METHOD(Point_Negation)
		{
			auto point = Point(1, 2);
			Assert::AreEqual(Point(-1, -2), -point);
		}

		TEST_METHOD(Point_Multiplication)
		{
			auto p = Point(2, 4);
			const float F = 1.5f;
			Assert::AreEqual(Point(3, 6), p * F);
			Assert::AreEqual(Point(3, 6), F * p);
			Assert::AreEqual(Point(4, 16), p * p);
		}

		TEST_METHOD(Point_Division)
		{
			auto p = Point(2, 4);
			const float F = 2;
			Assert::AreEqual(Point(1, 2), p / F);
			Assert::AreEqual(Point(1, 0.5f), F / p);
			Assert::AreEqual(Point(1, 8), p / Point(2, 0.5f));
		}

		TEST_METHOD(Point_ImplicitCastFromSize)
		{
			auto p = Point(1, 2);
			auto s = Size(1, 2);
			Point addition = p + s;
			Assert::AreEqual(Point(2, 4), addition);
		}

		TEST_METHOD(Point_Distance)
		{
			auto zero = Point();
			auto point = Point(3, 4);

			Assert::AreEqual(5.f, zero.DistanceTo(point));
			Assert::AreEqual(0.f, zero.DistanceTo(zero));
		}

		TEST_METHOD(Point_PointToString)
		{
			auto p = Point(3, 4);
			Assert::AreEqual("(3, 4)", p.ToString().ToCharArray());
		}

		TEST_METHOD(Point_PointToStringAndFromString)
		{
			auto point = Point(2.23f, 3.45f);
			String sizeString = point.ToString();
			Assert::AreEqual(point, Point(sizeString));
			Assert::ExpectException<Point::InvalidNumberOfComponents>([] { Point("abc"); });
		}

		TEST_METHOD(Point_Statics)
		{
			Assert::AreEqual(Point(0, 0), Point::Zero);
			Assert::AreEqual(Point(1, 1), Point::One);
			Assert::AreEqual(Point(0.5f, 0.5f), Point::Half);
			Assert::AreEqual(Point(1, 0), Point::UnitX);
			Assert::AreEqual(Point(0, 1), Point::UnitY);
		}
	};
}}}