#pragma once
#include "Object.h"

namespace DeltaEngine { namespace Core
{
	// http://msdn.microsoft.com/en-us/library/system.idisposable.aspx
	class CoreLibrary IDisposable : public virtual Object
	{
	public:
		virtual void Dispose() = 0;
		virtual ~IDisposable() throw() {}
	};
}}