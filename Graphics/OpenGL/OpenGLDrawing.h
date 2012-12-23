#pragma once
#include "Graphics/Drawing.h"
#include "GL/glew.h"
#include "OpenGLDevice.h"
#include "Hypodermic/AutowiredConstructor.h"

namespace DeltaEngine { namespace Graphics { namespace OpenGL
{
	// Allows to draw shapes on screen. Needs a graphic device.
#pragma warning(disable: 4275)
	class GraphicsOpenGLLibrary OpenGLDrawing : public Drawing
	{
	public:
		typedef Hypodermic::AutowiredConstructor<OpenGLDrawing(OpenGLDevice*)> AutowiredSignature;
		OpenGLDrawing(std::shared_ptr<OpenGLDevice> device);

		void SetColor(const Datatypes::Color& color);
		void DrawRectangle(const Datatypes::Rectangle& area);
		void Dispose() {}
	};
}}}