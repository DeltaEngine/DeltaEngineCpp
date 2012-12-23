#include "CppUnitTest.h"
#include "CppUnitTestCoreSupport.h"
#include "Core\Time.h"
#include "Core\StopwatchTime.h"
#include "MockElapsedTime.h"
#include "Core\CoreString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	TEST_CLASS(TimeTests)
	{
	public:
		TEST_METHOD(Time_RunTime)
		{
			auto time = Time(std::make_shared<MockElapsedTime>());
			time.Run();
			Assert::AreEqual(0LL, time.GetMilliseconds());
		}

		TEST_METHOD(Time_RunTimeWithStopwatch)
		{
			auto time = Time(std::make_shared<StopwatchTime>());
			time.Run();
			Assert::AreEqual(0LL, time.GetMilliseconds());
		}

		TEST_METHOD(Time_GetCurrentDelta)
		{
			auto time = Time(std::make_shared<MockElapsedTime>());
			time.Run();
			Assert::AreEqual(0.0f, time.GetCurrentDelta());
			time.Run();
			Assert::AreEqual(0.1f, time.GetCurrentDelta());
		}

		TEST_METHOD(Time_CheckEveryWithInvalidStepAlwaysReturnsTrue)
		{
			auto time = Time(std::make_shared<MockElapsedTime>());
			Assert::IsTrue(time.CheckEvery(-1));
		}

		TEST_METHOD(Time_CalculateFps)
		{
			auto time = Time(std::make_shared<MockElapsedTime>());
			do
				time.Run();
			while (!time.CheckEvery(1.0f));
			Assert::IsTrue(abs(time.GetFps() - 10) <= 1,
				(String("Fps=") + time.GetFps()).ToWString().c_str());
		}

		TEST_METHOD(Time_GetSecondsSinceStartToday)
		{
			auto time = Time(std::make_shared<MockElapsedTime>());
			Assert::AreEqual(0.0f, time.GetSecondsSinceStartToday());
			time.Run();
			Assert::AreNotEqual(0.0f, time.GetSecondsSinceStartToday());
		}

		TEST_METHOD(Time_GetFps)
		{
			auto time = Time(std::make_shared<StopwatchTime>());
			Assert::AreEqual(time.GetFps(), 60);
		}

		BEGIN_INTEGRATION_TEST(Time_CalculateFpsWithStopwatch)
		{
			auto time = Time(std::make_shared<StopwatchTime>());
			const int TargetFps = 50;
			do
			{
				Sleep(1000 / TargetFps);
				time.Run();
			} while (!time.CheckEvery(1.0f));
			Assert::IsTrue(abs(time.GetFps() - TargetFps) <= 8,
				String::Format("Fps=%i", time.GetFps()).ToWString().c_str());
		}
		END_INTEGRATION_TEST
	};
}}}