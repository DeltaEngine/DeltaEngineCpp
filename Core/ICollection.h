#pragma once
#include "IEnumerable.h"

namespace DeltaEngine { namespace Core
{
	// http://msdn.microsoft.com/en-us/library/92t2ye13.aspx
	template<typename Type>
	class ICollection : public virtual IEnumerable<Type>
	{
	public:
		virtual int GetCount() const = 0;
		virtual bool GetIsReadOnly() const = 0;
		virtual void Add(const Type& item) = 0;
		virtual void Clear() = 0;
		virtual void CopyTo(Type* array, int arrayIndex) const = 0;
		virtual bool Contains(Type item) = 0;
		virtual void Remove(const Type& item) = 0;
	};
}}