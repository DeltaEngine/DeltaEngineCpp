#pragma once
#include "Core\Presenter.h"
#include "Core\IDisposable.h"
#include "ScreenSpace.h"

namespace DeltaEngine { namespace Graphics
{
	// The graphics device clears everything (via Run) at the beginning of each frame and shows the
	// result of the render buffer on screen at the end of each frame (via Present).
	class Device : public Core::Presenter, public virtual Core::IDisposable
	{
	public:
		virtual const ScreenSpace* GetScreen() const = 0;
	};
}}