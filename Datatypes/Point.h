#pragma once
#include "Core\Object.h"
#include "Core\CoreString.h"
#include "Core\IEquatable.h"
#include "Core\Exception.h"

#ifdef LIB
#define DatatypesLibrary
#elif DATATYPES_EXPORT
#define DatatypesLibrary __declspec(dllexport)
#else
#define DatatypesLibrary __declspec(dllimport)
#endif

namespace DeltaEngine { namespace Datatypes
{
	class Size;

	// Represents a 2D vector, which is useful for screen positions (sprites, mouse, touch, etc.)
	class DatatypesLibrary Point : public virtual Core::IEquatable<Point>, public virtual Core::Object
	{
	public:
		Point(float x = 0, float y = 0);
		Point(Core::String pointAsString);

		class InvalidNumberOfComponents : public Core::Exception { };
		Point operator+(const Point& other) const;
		Point operator-(const Point& other) const;
		Point operator*(const float f) const;
		Point operator/(const float f) const;

		friend Point operator*(float f, const Point& p)
		{
			return Point(f * p.X, f * p.Y);
		}

		friend Point operator/(float f, const Point& p)
		{
			return Point(f / p.X, f / p.Y);
		}

		Point operator*(const Point& other) const;
		Point operator/(const Point& other) const;
		bool operator!=(const Point& other) const;
		bool operator==(const Point& other) const;
		Point operator-() const;
		operator Size() const;
		bool Equals(const Point& other) const;
		virtual unsigned int GetHashCode() const;
		virtual Core::String ToString() const;
		float DistanceTo(const Point& other) const;

		float X;
		float Y;

		static const Point Zero;
		static const Point One;
		static const Point Half;
		static const Point UnitX;
		static const Point UnitY;
	};
}}