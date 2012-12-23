#pragma once
#include "Runner.h"
#include "ElapsedTime.h"
#include "Hypodermic/AutowiredConstructor.h"
#include <memory>

namespace DeltaEngine { namespace Core
{
	// Provides the current app run time and delta time for the frame. All times are in seconds.
	class CoreLibrary Time : public virtual Runner
	{
	public:
		typedef Hypodermic::AutowiredConstructor<Time(ElapsedTime*)> AutowiredSignature;
		Time(std::shared_ptr<ElapsedTime> elapsed);

		int GetFps();
		float GetCurrentDelta();
		long long GetMilliseconds();
		void Run();
		bool CheckEvery(float timeStepInSeconds);
		// Returns an accurate seconds float value for today, would get inaccurate with more days.
		float GetSecondsSinceStartToday();

	private:
		void SetFpsTo60InitiallyAndSetUsefulInitialValues();
		void UpdateFpsEverySecond();

#pragma warning(disable: 4251)
		const std::shared_ptr<ElapsedTime> elapsed;
		int fps;
		int framesCounter;
		long long thisFrameTicks;
		long long lastFrameTicks;
		float currentDelta;
	};
}}