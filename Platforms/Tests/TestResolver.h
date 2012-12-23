#pragma once
#include "Platforms/Window.h"
#include "MockWindow.h"
#include "Graphics/Device.h"
#include "Platforms/HypodermicResolver.h"
#include "Core/StopwatchTime.h"
#include "Core/Time.h"
#include "Core/Tests/MockElapsedTime.h"
#include "Graphics/Tests/MockDevice.h"
#include "Graphics/Tests/MockDrawing.h"
#include "Rendering/Renderer.h"
#include "CppUnitTest.h"

namespace DeltaEngine { namespace Platforms { namespace Tests
{
	class TestResolver : public HypodermicResolver
	{
	public:
		TestResolver()
			: registeredMocks()
		{
			testStarted = NULL;
			Resolver::CurrentlyInAutomatedUnitTest = true;
			RegisterMockAs<MockWindow, Platforms::Window>();
			auto deviceMock = RegisterMockAs<Graphics::Tests::MockDevice, Graphics::Device>();
			auto drawingMock = RegisterMock<Graphics::Tests::MockDrawing, Graphics::Drawing>(
				std::make_shared<Graphics::Tests::MockDrawing>(deviceMock));
			RegisterMock<Rendering::Renderer, Rendering::Renderer>(
				std::make_shared<Rendering::Renderer>(drawingMock));
			RegisterMock<Core::Time, Core::Time>(std::make_shared<Core::Time>(
				std::make_shared<Core::Tests::MockElapsedTime>()));
		}

		~TestResolver() { Dispose(); }

		void Dispose()
		{
			WarnIfUnitTestTakesTooLong();
			HypodermicResolver::Dispose();
		}

	protected:
		void MakeSureContainerIsInitialized()
		{
			if (GetIsAlreadyInitialized())
				return;

			for (auto instance : registeredMocks)
				AddRunnerAndPresenterForExistingInstance(instance);

			HypodermicResolver::MakeSureContainerIsInitialized();
			testElapsedMs = GetTimeInMsForSlowTests();
		}

	private:
		template<typename Type, class Interface>
		std::shared_ptr<Type> RegisterMock(std::shared_ptr<Type> instance)
		{
			static_assert(std::is_convertible<Type, Core::Object>::value,
				"Must register types derived from Object!");
			static_assert(std::is_convertible<Type, Interface>::value,
				"Type must derive from Interface!");
			if (registeredMocks.Contains(instance))
				return instance;

			registeredMocks.Add(instance);
			return RegisterSingletonMock<Type, Interface>(instance);
		}

		template<typename Type, class Interface>
		std::shared_ptr<Type> RegisterMockAs()
		{
			return RegisterMock<Type, Interface>(std::make_shared<Type>());
		}

		void AddRunnerAndPresenterForExistingInstance(std::shared_ptr<Core::Object> instance)
		{
			RegisterInstanceAsRunnerOrPresenterIfPossible(instance);
		}

		long long GetTimeInMsForSlowTests()
		{
			if (testStarted != NULL)
				return testStarted->GetTicks();

			testStarted = new Core::StopwatchTime();
			return 0;
		}

		void WarnIfUnitTestTakesTooLong()
		{
			if (TookLongerThan10Ms())
				printf("This unit test takes too long (%lld ms, max. 10ms is allowed), please add "
				"Category(\"Slow\") to run it nightly instead!", testElapsedMs);
		}

		bool TookLongerThan10Ms()
		{
			testElapsedMs = GetTimeInMsForSlowTests() - testElapsedMs;
			return testElapsedMs > 10;
		}

		Core::List<std::shared_ptr<Core::Object>> registeredMocks;
		long long testElapsedMs;
		Core::StopwatchTime* testStarted;
	};
}}}