#pragma once

namespace DeltaEngine { namespace Core
{
	// http://msdn.microsoft.com/en-us/library/ms131187.aspx
	template<typename Type>
	class IEquatable
	{
	public:
		virtual bool operator==(const Type& element) const = 0;
	};
}}