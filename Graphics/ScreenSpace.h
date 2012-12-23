#pragma once
#include "Datatypes/Size.h"
#include "Datatypes/Point.h"
#include "Datatypes/Rectangle.h"
#include "Core/MathExtensions.h"

#ifdef LIB
#define GraphicsLibrary
#elif GRAPHICS_EXPORT
#define GraphicsLibrary __declspec(dllexport)
#else
#define GraphicsLibrary __declspec(dllimport)
#endif

namespace DeltaEngine { namespace Graphics
{
	// Converts to and from quadratic space. Must be created whenever the viewport size changes.
	class GraphicsLibrary ScreenSpace
	{
	public:
		ScreenSpace(const Datatypes::Size& viewportPixelSize);

		Datatypes::Point ToQuadraticSpace(const Datatypes::Point& pixelPosition) const;
		Datatypes::Size ToQuadraticSpace(const Datatypes::Size& pixelSize) const;
		Datatypes::Rectangle ToQuadraticSpace(const Datatypes::Rectangle& quadraticRect) const;
		Datatypes::Point ToPixelSpace(const Datatypes::Point& quadraticPos) const;
		Datatypes::Size ToPixelSpace(const Datatypes::Size& quadraticSize) const;
		Datatypes::Rectangle ToPixelSpace(const Datatypes::Rectangle& quadraticRect) const;
		Datatypes::Point GetTopLeft() const;
		Datatypes::Point GetBottomRight() const;
		Datatypes::Size GetArea() const;
		Datatypes::Rectangle GetViewport() const;
		Datatypes::Size GetViewportPixelSize() const;

	private:
		const Datatypes::Size viewportPixelSize;
		const float aspectRatio;
		const Datatypes::Size quadraticToPixelScale;
		const Datatypes::Point quadraticToPixelOffset;
		const Datatypes::Size pixelToQuadraticScale;
		const Datatypes::Point pixelToQuadraticOffset;

		Datatypes::Size CalculateToPixelScale() const;
		Datatypes::Point CalculateToPixelOffset() const;
		Datatypes::Size CalculateToQuadraticScale() const;
		Datatypes::Point CalculateToQuadraticOffset() const;
	};
}}