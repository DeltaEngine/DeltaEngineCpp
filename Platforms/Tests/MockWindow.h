#pragma once
#include "Platforms/Window.h"
#include "Core/CoreString.h"
#include "Datatypes/Size.h"

namespace DeltaEngine { namespace Platforms { namespace Tests
{
	class MockWindow : public Window
	{
	public:
		void SetTitle(Core::String value ) {}
		Core::String GetTitle() { return "MockWindow"; }
		bool GetIsVisible() { return true; }
		void* GetHandle() { return NULL; }
		Datatypes::Size GetViewportSize() { return Datatypes::Size(800, 600); }
		void SetTotalSize( const Datatypes::Size& value ) {}
		Datatypes::Size GetTotalSize() { return Datatypes::Size(800, 600); }
		void SetBackgroundColor( const Datatypes::Color& value ) {}
		Datatypes::Color GetBackgroundColor() { return Datatypes::Color::Black; }
		void SetIsFullscreen( bool value ) {}
		bool GetIsFullscreen() { return false; }
		bool GetIsClosing() { return true; }
		void Close() {}

	protected:
		void Dispose() {}
	};
}}}