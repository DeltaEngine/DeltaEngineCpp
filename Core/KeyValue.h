#pragma once
#include "Object.h"

namespace DeltaEngine { namespace Core
{
	// Storage class for two objects as Key and Value
	class CoreLibrary KeyValue : public virtual Object
	{
	public:
		KeyValue();
		KeyValue(const Object* key, Object* value);
		bool operator==(const KeyValue other) const
		{
			return Key == other.Key && Value == other.Value;
		}

		const Object* Key;
		Object* Value;
	};
}}