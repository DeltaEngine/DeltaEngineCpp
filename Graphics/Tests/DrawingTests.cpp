#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "Datatypes/Tests/CppUnitTestDatatypesSupport.h"
#include "MockDrawing.h"
#include "MockDevice.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Datatypes;

namespace DeltaEngine { namespace Graphics { namespace Tests
{
	TEST_CLASS(DrawingTests)
	{
	public:
		TEST_METHOD(Drawing_DrawColoredRectangle)
		{
			MockDrawing mockDrawing(std::make_shared<MockDevice>());
			mockDrawing.SetColor(Color::Red);
			mockDrawing.DrawRectangle(Rectangle::One);
			AreEqual("(R=255, G=0, B=0, A=255), (0, 0, 1, 1)", mockDrawing.GetResult());
			mockDrawing.Dispose();
		}

		TEST_METHOD(Drawing_CheckDeviceScreenSpace)
		{
			auto device = std::make_shared<MockDevice>();
			auto screen = device->GetScreen();
			AreEqual(Point::Zero, screen->GetTopLeft());
			AreEqual(Point::One, screen->GetBottomRight());
			Assert::AreEqual((void*)device->GetScreen(), (void*)device->GetScreen());
		}
	};
}}}