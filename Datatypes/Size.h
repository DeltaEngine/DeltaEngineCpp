#pragma once
#include "Core/Object.h"
#include "Core/CoreString.h"
#include "Core/Exception.h"
#include "Point.h"

namespace DeltaEngine { namespace Datatypes
{
	class Point;

	// Holds the width and height of an object (e.g. a rectangle)
	class DatatypesLibrary Size : public virtual Core::Object
	{
	public:
		Size(float width = 0, float height = 0);
		Size(Core::String sizeAsString);

		class InvalidNumberOfComponents : public Core::Exception { };
		bool operator==(const Size& other) const;
		bool operator!=(const Size& other) const;
		bool operator>=(const Size& other) const;
		bool operator>(const Size& other) const;
		bool operator<(const Size& other) const;
		Size operator*(const Size& other) const;
		Size operator*(const float f) const;
		Size operator/(const float f) const;

		friend Size operator*(float f, const Size& s)
		{
			return Size(f * s.Width, f * s.Height);
		}

		friend Size operator/(float f, const Size& s)
		{
			return Size(f / s.Width, f / s.Height);
		}

		Size operator+(const Size& other) const;
		Size operator-(const Size& other) const;
		bool Equals(const Size& other) const;
		operator Point() const;
		virtual unsigned int GetHashCode() const;
		virtual Core::String ToString() const;
		static Size Lerp(Size& size1, Size& size2, float percentage);
		float GetAspect() const;

		float Width;
		float Height;

		static const Size Zero;
		static const Size One;
		static const Size Half;
	};
}}