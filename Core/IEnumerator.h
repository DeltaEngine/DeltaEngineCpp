#pragma once
#include "Object.h"
#include <list>

namespace DeltaEngine { namespace Core 
{
	// http://msdn.microsoft.com/en-us/library/system.collections.ienumerator.aspx
	template<typename Type>
	class IEnumerator
	{
	public:
		virtual Type GetCurrent() const = 0;
		virtual bool MoveNext() = 0;
		virtual void Reset() = 0;
	};
}}