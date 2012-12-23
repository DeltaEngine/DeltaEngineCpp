#pragma once
#include "Platforms\Window.h"
#include "Datatypes\Rectangle.h"
#include "Core\Runner.h"
#include "Core\Exception.h"
#include <windows.h>

#ifdef LIB
#define PlatformsWindowsLibrary
#elif PLATFORMS_WINDOWS_EXPORT
#define PlatformsWindowsLibrary __declspec(dllexport)
#else
#define PlatformsWindowsLibrary __declspec(dllimport)
#endif

namespace DeltaEngine { namespace Platforms { namespace Windows
{
	// WINAPI Win32 window to host the device surface for rendering (see OpenGLWindow for details).
#pragma warning(disable: 4275)
	class PlatformsWindowsLibrary Win32Window : public Window, public Core::Runner
	{
	public:
		Win32Window(WNDCLASSEX& windowData);
		~Win32Window();

		virtual void SetTitle(Core::String title);
		virtual Core::String GetTitle();
		virtual void SetTotalSize(const Datatypes::Size& size);
		virtual Datatypes::Size GetTotalSize();
		virtual Datatypes::Size GetViewportSize();
		virtual bool GetIsVisible();
		virtual void* GetHandle();
		virtual void SetBackgroundColor(const Datatypes::Color& value);
		virtual Datatypes::Color GetBackgroundColor();
		virtual void SetIsFullscreen(bool value);
		virtual bool GetIsFullscreen();
		virtual bool GetIsClosing();
		virtual void Close();
		virtual void Run();
		virtual LRESULT HandleMessage(UINT windowMessage, WPARAM wParam, LPARAM lParam);

		class WindowException : public Core::Exception
		{
		public:
			WindowException()
				: lastError(GetLastError()) {}

			Core::String ToString() const
			{
				return Core::Exception::ToString() + " LastError=" + lastError + "\n";
			}

		private:
			DWORD lastError;
		};
		class CreateWindowHandleFailed : public WindowException {};
		class CreateDeviceContextFailed : public WindowException {};
		class ReleaseDeviceContextFailed : public WindowException {};
		class DestroyWindowFailed : public WindowException {};
		class UnregisterClassFailed : public WindowException {};

	protected:
		void Dispose();

		HDC gdiDeviceContext;

	private:
		Datatypes::Size GetSizeUsing(BOOL (__stdcall *getRect) (HWND, LPRECT));
		void RegisterWindow();
		void CreateWindowHandle();
		void CreateDeviceContext();
		void Show();
		void ReleaseDeviceContext();
		void DisposeWindowHandle();
		void UnregisterWindow();

		HWND handle;
		WNDCLASSEX data;
		DWORD style;
		DWORD extendedStyle;
		Core::String title;
		Datatypes::Size currentSize;
		bool isFullscreen;
		Datatypes::Color backGroundColor;
		bool isClosing;
	};
}}}