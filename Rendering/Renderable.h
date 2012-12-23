#pragma once
#include "Core/IDisposable.h"
#include <memory>

#ifdef LIB
#define RenderingLibrary
#elif RENDERING_EXPORT
#define RenderingLibrary __declspec(dllexport)
#else
#define RenderingLibrary __declspec(dllimport)
#endif

namespace DeltaEngine { namespace Rendering
{
	class Renderer;

	// Renders anything automatically until disposed. Used in Drawing and many Rendering classes.
	class RenderingLibrary Renderable : public virtual Core::IDisposable
	{
	public:
		~Renderable() { Dispose(); }
		virtual void Dispose();

		virtual void Render() = 0;

	protected:
		Renderable(std::shared_ptr<Renderer> renderer);
#pragma warning(disable: 4251)
		std::shared_ptr<Renderer> renderer;
	};
}}