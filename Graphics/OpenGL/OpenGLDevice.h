#pragma once
#include "Graphics/Device.h"
#include "Platforms/Window.h"
#include "Hypodermic/AutowiredConstructor.h"
#include <memory>
#include <windows.h>

#ifdef LIB
#define GraphicsOpenGLLibrary
#elif GRAPHICS_OPENGL_EXPORT
#define GraphicsOpenGLLibrary __declspec(dllexport)
#else
#define GraphicsOpenGLLibrary __declspec(dllimport)
#endif

namespace DeltaEngine { namespace Graphics { namespace OpenGL
{
	// OpenGL device implementation
#pragma warning(disable: 4275)
	class GraphicsOpenGLLibrary OpenGLDevice : public Device
	{
	public:
		typedef Hypodermic::AutowiredConstructor<OpenGLDevice(Platforms::Window*)> AutowiredSignature;
		OpenGLDevice(std::shared_ptr<Platforms::Window> window);
		~OpenGLDevice() { Dispose(); }
		void Dispose();

		void Run();
		void Present();
		const ScreenSpace* GetScreen() const { return screen.get(); }

	private:
		std::shared_ptr<ScreenSpace> screen;
		std::shared_ptr<Platforms::Window> window;
		HDC deviceContext;
		HGLRC graphicsContext;

		void InitGL21();
		void InitializeProjectionMatrix();

		static void InitializeModelViewMatrix();
	};
}}}