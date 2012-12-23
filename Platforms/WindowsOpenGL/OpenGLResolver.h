#pragma once
#include "OpenGLWindow.h"
#include "Platforms/Windows/WindowsResolver.h"
#include "Graphics/OpenGL/OpenGLDrawing.h"
#include "Core/CoreString.h"

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

namespace DeltaEngine { namespace Platforms
{
	class OpenGLResolver final : public Windows::WindowsResolver
	{
	public:
		OpenGLResolver()
		{
#ifdef _DEBUG
			InitializeExceptionHandler();
			SetupMemoryLeakDetectionInDebugMode();
#endif
			RegisterSingleton<OpenGLWindow, Window>([&](Hypodermic::IComponentContext& c)
			{
				return new OpenGLWindow(BuildWindowData());
			});

			AutowireSingleton<Graphics::OpenGL::OpenGLDevice, Graphics::Device>();
			AutowireSingleton<Graphics::OpenGL::OpenGLDrawing, Graphics::Drawing>();
		}

	private:
#ifdef _DEBUG
		void InitializeExceptionHandler()
		{
		 SetUnhandledExceptionFilter(UnhandledExceptionHandler);
		}

		static LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* ExceptionInfo)
		{
			// This needs improvement in the future once we run into more unhandled exception trouble!
			OutputDebugStringA(Core::String::Format("Unhandled Exception occurred 0x%08x at 0x%08x\n",
				ExceptionInfo->ExceptionRecord->ExceptionCode,
				ExceptionInfo->ExceptionRecord->ExceptionAddress).ToCharArray());
			return EXCEPTION_CONTINUE_SEARCH;
		}

		void SetupMemoryLeakDetectionInDebugMode() 
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			// _CRTDBG_MODE_WNDW can be used to force fixing problems right away.
			_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
			// Use _CrtSetBreakAlloc to find leaks and break when they are happening!
			// http://DeltaEngine.net/About/CodingStyleCpp#MemoryLeaks
		}
#endif
	};
}}