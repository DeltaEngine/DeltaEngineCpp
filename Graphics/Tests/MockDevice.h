#pragma once
#include "Graphics\Device.h"
#include "Datatypes\Size.h"

namespace DeltaEngine { namespace Graphics { namespace Tests 
{
	class MockDevice : public Device
	{
	public:
		MockDevice()
			: screen(ScreenSpace(Datatypes::Size::One)) {}
		~MockDevice() { Dispose(); }
		void Dispose() {}

		void Present() {}
		void Run() {}
		const ScreenSpace* GetScreen() const { return &screen; }

	private:
		const ScreenSpace screen;
	};
}}}