#pragma once

#ifdef LIB
#define CoreLibrary
#elif CORE_EXPORT
#define CoreLibrary __declspec(dllexport)
#else
#define CoreLibrary __declspec(dllimport)
#endif

namespace DeltaEngine { namespace Core
{
	class String;

	// http://msdn.microsoft.com/en-us/library/system.object.aspx
	class CoreLibrary Object
	{
	public:
		virtual String ToString() const;
		virtual unsigned int GetHashCode() const;
	};
}}