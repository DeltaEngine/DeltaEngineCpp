#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "CppUnitTestDatatypesSupport.h"
#include "Datatypes/Size.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Datatypes;
using namespace DeltaEngine::Core;

namespace DeltaEngine { namespace Datatypes { namespace Tests
{
	TEST_CLASS(SizeTests)
	{
	public:
		TEST_METHOD(Size_CreateFromFloat)
		{
			auto size = Size(3.51f, 0.23f);
			Assert::AreEqual(size.Width, 3.51f);
			Assert::AreEqual(size.Height, 0.23f);
		}

		TEST_METHOD(Size_Equals)
		{
			auto s1 = Size(1, 2);
			Assert::IsTrue(s1 != Size(3, 4));
			Assert::IsFalse(s1 != Size(1, 2));
			Assert::IsTrue(s1 == Size(1, 2));
		}

		TEST_METHOD(Size_GreaterOrEqual)
		{
			auto s1 = Size(1, 2);
			auto s2 = Size(2, 3);
			Assert::IsTrue(s2 >= s1);
			Assert::IsFalse(s1 >= s2);
			Assert::IsTrue(s1 >= s1);
		}

		TEST_METHOD(Size_PlusOperator)
		{
			auto plus = Size(2, 2) + Size(3, 3);
			Assert::AreEqual(Size(5, 5), plus);
		}

		TEST_METHOD(Size_MinusOperator)
		{
			auto minus = Size(2, 2) - Size(1, 1);
			Assert::AreEqual(Size(1, 1), minus);
		}

		TEST_METHOD(Size_MultiplyOperator)
		{
			auto multiply = Size(2, 2) * Size(3, 5);
			Assert::AreEqual(Size(6, 10), multiply);
		}

		TEST_METHOD(Size_MultiplyByFloat)
		{
			Assert::AreEqual(Size(5, 10), (Size(2, 4) * 2.5f));
			Assert::AreEqual(Size(5, 10), 2.5f * (Size(2, 4)));
		}

		TEST_METHOD(Size_DivideSizeByFloat)
		{
			auto s = Size(4, 5);
			const float F = 2.0f;
			Size divide = s / F;
			Assert::AreEqual(divide, Size(2.0f, 2.5f));
		}

		TEST_METHOD(Size_DivideFloatBySize)
		{
			const float F = 2.0f;
			auto s = Size(4, 5);
			Size divide = F / s;
			Assert::AreEqual(divide, Size(0.5f, 0.4f));
		}

		TEST_METHOD(Size_ExplicitCastFromPoint)
		{
			auto p = Point(1, 2);
			auto s = Size(1, 2);
			Size addition = (Size)p + s;
			Assert::AreEqual(Size(2, 4), addition);
		}

		TEST_METHOD(Size_SizeToString)
		{
			auto size = Size(2.23f, 3.45f);
			Assert::AreEqual("(2.23, 3.45)", size.ToString().ToCharArray());
		}

		TEST_METHOD(Size_SizeToStringAndFromString)
		{
			auto size = Size(2.23f, 3.45f);
			String sizeString = size.ToString();
			Assert::AreEqual(size, Size(sizeString));
			Assert::ExpectException<Size::InvalidNumberOfComponents>([] { Size("abc"); });
		}

		TEST_METHOD(Size_Lerp)
		{
			auto size1 = Size(10, 20);
			auto size2 = Size(20, 30);
			auto lerp20 = Size(12, 22);
			Assert::AreEqual(lerp20, Size::Lerp(size1, size2, 0.2f));
			Assert::AreEqual(size1, Size::Lerp(size1, size2, -1.0f));
			Assert::AreEqual(size2, Size::Lerp(size1, size2, 1.1f));
		}

		TEST_METHOD(Size_GetAspect)
		{
			auto portrait = Size(0.5f, 1.0f);
			Size square = Size::One;
			auto landscape = Size(1.0f, 0.5f);
			Assert::AreEqual(0.5f, portrait.GetAspect());
			Assert::AreEqual(1.0f, square.GetAspect());
			Assert::AreEqual(2.0f, landscape.GetAspect());
		}

		TEST_METHOD(Size_Statics)
		{
			Assert::AreEqual(Size(), Size::Zero);
			Assert::AreEqual(Size(0.0f, 0.0f), Size::Zero);
			Assert::AreEqual(Size(1.0f, 1.0f), Size::One);
			Assert::AreEqual(Size(0.5f, 0.5f), Size::Half);
		}
	};
}}}