#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "CppUnitTestDatatypesSupport.h"
#include "Datatypes/Color.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Datatypes;

namespace DeltaEngine { namespace Datatypes { namespace Tests
{
	TEST_CLASS(ColorTests)
	{
	public:
		TEST_METHOD(Color_Create)
		{
			AssertCreation<float>(255.f);
			AssertCreation<byte>(1);
		}

		TEST_METHOD(Color_Equals)
		{
			auto c1 = Color((byte)255, 128, 255);
			auto c2 = Color((byte)255, 255, 0);
			auto c3 = Color((byte)255, 128, 255);

			Assert::IsTrue(c1 != c2);
			Assert::IsFalse(c1 != c3);
			Assert::IsTrue(c1 == c3);
			Assert::IsFalse(c1 == c2);
			Assert::IsTrue(c1.Equals(c3));
			Assert::IsFalse(c1.Equals(c2));
		}

		TEST_METHOD(Color_ToString)
		{
			AreEqual("(R=10, G=20, B=30, A=40)", Color((byte)10, 20, 30, 40).ToString());
			AreEqual("(R=255, G=255, B=255, A=255)", Color::White.ToString());
		}

		TEST_METHOD(Color_GetRandomBrightColor)
		{
			auto color = Color::GetRandomBrightColor();

			Assert::IsTrue(color.R > 127);
			Assert::IsTrue(color.G > 127);
			Assert::IsTrue(color.B > 127);
			Assert::IsTrue(color.A == 255);
			Assert::AreNotEqual(color, Color::GetRandomBrightColor());
		}

		TEST_METHOD(Color_Lerp)
		{
			auto color1 = Color((byte)10, 20, 30, 40);
			auto color2 = Color((byte)20, 30, 40, 50);
			auto lerp20 = Color((byte)12, 22, 32, 42);

			Assert::AreEqual(lerp20, Color::Lerp(color1, color2, 0.2f));
			Assert::AreEqual(color1, Color::Lerp(color1, color2, -1));
			Assert::AreEqual(color2, Color::Lerp(color1, color2, 1.1f));
		}

		TEST_METHOD(Color_Statics)
		{
			Assert::AreEqual(Color((byte)0, 0, 0), Color::Black);
			Assert::AreEqual(Color((byte)0, 0, 255), Color::Blue);
			Assert::AreEqual(Color((byte)100, 149, 237), Color::CornflowerBlue);
			Assert::AreEqual(Color((byte)0, 255, 255), Color::Cyan);
			Assert::AreEqual(Color((byte)128, 128, 128), Color::Gray);
			Assert::AreEqual(Color((byte)0, 255, 0), Color::Green);
			Assert::AreEqual(Color((byte)152, 251, 152), Color::PaleGreen);
			Assert::AreEqual(Color((byte)255, 192, 203), Color::Pink);
			Assert::AreEqual(Color((byte)255, 0, 255), Color::Purple);
			Assert::AreEqual(Color((byte)255, 0, 0), Color::Red);
			Assert::AreEqual(Color((byte)255, 255, 255), Color::White);
			Assert::AreEqual(Color((byte)255, 255, 0), Color::Yellow);
		}

	private:
		template <typename Scale> 
		void AssertCreation(Scale scale)
		{
			byte r = 230, g = 197, b = 34, a = 255;
			Color color = Color((Scale)(r / scale), g / scale, b / scale, a / scale);

			Assert::AreEqual(r, color.R);
			Assert::AreEqual(g, color.G);
			Assert::AreEqual(b, color.B);
			Assert::AreEqual(a, color.A);
		}
	};
}}}