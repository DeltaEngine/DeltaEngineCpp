#pragma once
#include "Platforms/HypodermicResolver.h"
#include "Win32Window.h"
#include "Core/StopwatchTime.h"
#include "Core/Time.h"
#include "Hypodermic/Helpers.h"
#include "Rendering/Renderer.h"

namespace DeltaEngine { namespace Platforms { namespace Windows
{
	class WindowsResolver : public HypodermicResolver
	{
	protected:
		WindowsResolver()
		{
			RegisterSingleton<Win32Window, Window>([&](Hypodermic::IComponentContext& c)
			{
				return new Win32Window(BuildWindowData());
			});

			AutowireSingletonAsSelf<Rendering::Renderer>();
			AutowireSingleton<Core::StopwatchTime, Core::ElapsedTime>();
			AutowireSingletonAsSelf<Core::Time>();
		}

	protected:
		WNDCLASSEX BuildWindowData()
		{
			WNDCLASSEX data = {0};
			data.cbSize = sizeof(data);
			data.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			data.lpfnWndProc = (WNDPROC)[](HWND	handle, UINT message, WPARAM wParam, LPARAM lParam)
			{
				Win32Window* window = NULL;
				if (message == WM_NCCREATE)
				{
					window = (Win32Window*)((CREATESTRUCT*)lParam)->lpCreateParams;
					SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)window);
				}
				else
					window = (Win32Window*)GetWindowLongPtr(handle, GWLP_USERDATA);

				if ((window != NULL) && (window->GetHandle() != NULL))
					return window->HandleMessage(message, wParam, lParam);

				return DefWindowProc(handle, message, wParam, lParam);
			};
			data.cbClsExtra = NULL;
			data.cbWndExtra = NULL;
			data.hInstance = (HINSTANCE)GetModuleHandle(NULL);
			// Try app icon, usually IDI_ICON1 = 101
			data.hIcon = LoadIcon(data.hInstance, MAKEINTRESOURCE(101));
			if (data.hIcon == NULL)
				data.hIcon = LoadIcon(NULL, IDI_WINLOGO);
			data.hCursor = LoadCursor(NULL, IDC_ARROW);
			data.hbrBackground = NULL;
			data.lpszMenuName = NULL;
			data.lpszClassName = L"DeltaEngineWin32Window";
			return data;
		}
	};
}}}