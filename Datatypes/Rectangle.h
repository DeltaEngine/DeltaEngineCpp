#pragma once
#include "Core/Object.h"
#include "Core/Exception.h"
#include "Core/CoreString.h"
#include "Point.h"
#include "Size.h"

namespace DeltaEngine { namespace Datatypes
{
	// Holds data for a rectangle by specifying its top left corner and the width and height.
	class DatatypesLibrary Rectangle : public virtual Core::Object
	{
	public:
		Rectangle(float top = 0, float left = 0, float width = 0, float height = 0);
		Rectangle(const Point& position, const Size& size);
		Rectangle(Core::String rectangleAsString);

		class InvalidNumberOfComponents : public Core::Exception { };
		float GetLeft() const;
		void SetLeft(float value);
		float GetTop() const;
		void SetTop(float value);
		float GetWidth() const;
		void SetWidth(float value);
		float GetHeight() const;
		void SetHeight(float value);
		float GetRight() const;
		void SetRight(float value);
		float GetBottom() const;
		void SetBottom(float value);
		Point GetTopRight() const;
		void SetTopRight(const Point& value);
		Point GetBottomLeft() const;
		void SetBottomLeft(const Point& value);
		Point GetBottomRight() const;
		void SetBottomRight(const Point& value);
		Point GetCenter() const;
		void SetCenter(const Point& value);
		float GetAspect() const;
		static Rectangle FromCenter(const Point& center, const Size& size);
		bool operator==(const Rectangle& other) const;
		bool operator!=(const Rectangle& other) const;
		bool Equals(const Rectangle& other) const;
		virtual unsigned int GetHashCode() const;
		bool Contains(const Point& position) const;
		virtual Core::String ToString() const;

		Point TopLeft;
		Size _Size;

		static const Rectangle Zero;
		static const Rectangle One;
	};
}}