#pragma once
#include "Object.h"

namespace DeltaEngine { namespace Core
{
	// http://msdn.microsoft.com/en-us/library/system.icloneable.aspx
	class CoreLibrary ICloneable
	{
	public:
		virtual Object* Clone() const = 0;
	};
}}