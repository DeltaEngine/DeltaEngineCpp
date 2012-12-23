#pragma once
#include "Core\Object.h"
#include "Core\IEquatable.h"
#include "Point.h"

typedef unsigned char byte;

namespace DeltaEngine { namespace Datatypes
{
	// Color with a byte or float per component (red, green, blue, alpha)
	class DatatypesLibrary Color : public virtual Core::IEquatable<Color>, public virtual Core::Object
	{
	public:
		Color(byte r = 0, byte g = 0, byte b = 0, byte a = 255);
		Color(float r, float g, float b, float a = 1.0f);
		bool Equals(const Color& other) const;
		bool operator==(const Color& other) const;
		bool operator!=(const Color& other) const;
		int GetPackedArgb() const;
		virtual unsigned int GetHashCode() const;
		virtual Core::String ToString() const;
		static Color Lerp(Color color1, Color color2, float percentage);
		static Color GetRandomBrightColor();

		byte R;
		byte G;
		byte B;
		byte A;

		static const Color Black;
		static const Color Blue;
		static const Color CornflowerBlue;
		static const Color Cyan;
		static const Color Gray;
		static const Color Green;
		static const Color PaleGreen;
		static const Color Pink;
		static const Color Purple;
		static const Color Red;
		static const Color White;
		static const Color Yellow;
	};
}}