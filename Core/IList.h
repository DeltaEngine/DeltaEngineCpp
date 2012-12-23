#pragma once
#include "ICollection.h"

namespace DeltaEngine { namespace Core
{
	// http://msdn.microsoft.com/en-us/library/5y536ey6.aspx
	template<typename Type>
	class IList : public virtual ICollection<Type>
	{
	public:
		virtual int IndexOf(const Type& item) = 0;
		virtual void Insert(int index, const Type& item) = 0;
		virtual void RemoveAt(int index) = 0;
		virtual Type& operator[](int index) const = 0;
	};
}}