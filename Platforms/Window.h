#pragma once
#include "Core\Object.h"
#include "Core\IDisposable.h"
#include "Datatypes\Size.h"
#include "Datatypes\Color.h"
#include <functional>
#include "Hypodermic/AutowiredConstructor.h"

namespace DeltaEngine { namespace Platforms
{
	// Window form the application is running in. In Windows this is done with Windows Forms or WPF.
	class Window : public virtual Core::Object, public virtual Core::IDisposable
	{
	public:
		virtual void SetTitle(Core::String value) = 0;
		virtual Core::String GetTitle() = 0;
		virtual bool GetIsVisible() = 0;
		virtual void* GetHandle() = 0;
		virtual Datatypes::Size GetViewportSize() = 0;
		std::function<void(Datatypes::Size)> ViewportSizeChanged;
		virtual void SetTotalSize(const Datatypes::Size& value) = 0;
		virtual Datatypes::Size GetTotalSize() = 0;
		virtual void SetBackgroundColor(const Datatypes::Color& value) = 0;
		virtual Datatypes::Color GetBackgroundColor() = 0;
		virtual void SetIsFullscreen(bool value) = 0;
		virtual bool GetIsFullscreen() = 0;
		virtual bool GetIsClosing() = 0;
		virtual void Close() = 0;
	};
}}