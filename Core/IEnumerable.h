#pragma once
#include "IEnumerator.h"
#include <list>
#include <memory>

namespace DeltaEngine { namespace Core 
{
	// http://msdn.microsoft.com/en-us/library/system.collections.ienumerable.aspx
	template<typename Type>
	class IEnumerable
	{
	public:
		virtual std::shared_ptr<IEnumerator<Type>> GetEnumerator() const = 0;
	};
}}