#include "Datatypes/Point.h"
#include "Datatypes/Size.h"
#include "Datatypes/Rectangle.h"
#include "Datatypes/Color.h"

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework
{
	template<> static std::wstring ToString<DeltaEngine::Datatypes::Point>(
		const DeltaEngine::Datatypes::Point& t) { return t.ToString().ToWString(); }
	template<> static std::wstring ToString<DeltaEngine::Datatypes::Size>(
		const DeltaEngine::Datatypes::Size& t) { return t.ToString().ToWString(); }
	template<> static std::wstring ToString<DeltaEngine::Datatypes::Rectangle>(
		const DeltaEngine::Datatypes::Rectangle& t) { return t.ToString().ToWString(); }
	template<> static std::wstring ToString<DeltaEngine::Datatypes::Color>(
		const DeltaEngine::Datatypes::Color& t) { return t.ToString().ToWString(); }

	static void AreEqual(const DeltaEngine::Datatypes::Point& expected,
		const DeltaEngine::Datatypes::Point& actual)
	{
		Assert::AreEqual(expected.X, actual.X);
		Assert::AreEqual(expected.Y, actual.Y);
	}

	static void AreEqual(const DeltaEngine::Datatypes::Size& expected,
		const DeltaEngine::Datatypes::Size& actual)
	{
		Assert::AreEqual(expected.Width, actual.Width);
		Assert::AreEqual(expected.Height, actual.Height);
	}

	static void AreEqual(const DeltaEngine::Datatypes::Rectangle& expected,
		const DeltaEngine::Datatypes::Rectangle& actual)
	{
		AreEqual(expected.TopLeft, actual.TopLeft);
		AreEqual(expected._Size, actual._Size);
	}

	static void AreEqual(const DeltaEngine::Datatypes::Color& expected,
		const DeltaEngine::Datatypes::Color& actual)
	{
		Assert::AreEqual(expected.GetPackedArgb(), actual.GetPackedArgb());
	}
}}}