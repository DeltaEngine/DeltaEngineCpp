#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "Platforms/Tests/TestAppOnce.h"
#include "Samples/LogoApp/LogoGame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Platforms::Tests;

namespace LogoApp { namespace Tests
{
	TEST_CLASS(LogoGameTests)
	{
	public:
		TEST_METHOD(LogoGame_Start)
		{
			TestAppOnce::Start<LogoGame>();
		}

		TEST_METHOD(LogoGame_RunFewTimesAndCloseGame)
		{
			TestAppOnce::Start<LogoGame>([](std::shared_ptr<LogoGame> game)
			{
				Assert::IsNotNull(game.get());
				for (int i = 0; i < 50; i++)
					game->Run();
			});
		}
	};
}}