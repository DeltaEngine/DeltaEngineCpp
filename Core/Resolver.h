#pragma once
#include "IDisposable.h"
#include "Object.h"
#include "List.h"
#include "Runner.h"
#include "Presenter.h"
#include <memory>

namespace DeltaEngine { namespace Core 
{
	// Base resolver method definitions and functionally to run runners and presenters.
	class CoreLibrary Resolver : public virtual IDisposable
	{
	public:
		Resolver();
		~Resolver() { Dispose(); }
		void Dispose();

		void RunAllRunners();
		void RunAllPresenters();

		static bool CurrentlyInAutomatedUnitTest;
		static bool CurrentlyInIntegrationTest;

	protected:
		void RegisterInstanceAsRunnerOrPresenterIfPossible(std::shared_ptr<Object> instance);

		List<std::shared_ptr<Runner>> runners;
		List<std::shared_ptr<Presenter>> presenters;

	private:
		bool isAlreadyDisposed;

		void TryToDispose(std::shared_ptr<IDisposable> disposable);
	};
}}