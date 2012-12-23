#include "Renderable.h"
#include "Renderer.h"

namespace DeltaEngine { namespace Rendering
{
	// Keeps position, size and color for an automatically rendered rectangle on screen.
	class RenderingLibrary ColoredRectangle : public Renderable
	{
	public:
		ColoredRectangle(std::shared_ptr<Renderer> render, const Datatypes::Rectangle& rect,
			const Datatypes::Color& color);
		ColoredRectangle(std::shared_ptr<Renderer> render, const Datatypes::Point& center,
			const Datatypes::Size& size, const Datatypes::Color& color);
		~ColoredRectangle() { Dispose(); }

		Datatypes::Rectangle Rect;
		Datatypes::Color Color;

		virtual void Render();
	};
}}