#pragma once
#include "Platforms\WIndows\Win32Window.h"

#ifdef LIB
#define WindowsOpenGLLibrary
#elif WINDOWSOPENGL_EXPORT
#define WindowsOpenGLLibrary __declspec(dllexport)
#else
#define WindowsOpenGLLibrary __declspec(dllimport)
#endif

namespace DeltaEngine { namespace Platforms
{
	// OpenGL compatible window for Windows to host the device surface for rendering.
	class WindowsOpenGLLibrary OpenGLWindow : public Windows::Win32Window
	{
	public:
		OpenGLWindow(WNDCLASSEX& windowData);
		~OpenGLWindow();

		class NoSuitablePixelFormatFound : public WindowException {};
		class SetPixelFormatFailed : public WindowException {};
		class CreateRenderingContextFailed : public WindowException {};
		class RenderingContextActivationFailed : public WindowException {};
		class DetachRenderingContextFailed : public WindowException {};
		class ReleaseRenderingContextFailed : public WindowException {};

	private:
		void Dispose();

		void ApplyPixelFormat();
		void CreateRenderingContext();
		void ActivateRenderingContext();
		void UpdateBackBuffer();
		PIXELFORMATDESCRIPTOR GetPixelFormatDescriptor();
		void ReleaseRenderingContext();

		HGLRC permanentRenderingContext;
		int colorDepthInBits;
		int depthBufferInBits;
	};
}}