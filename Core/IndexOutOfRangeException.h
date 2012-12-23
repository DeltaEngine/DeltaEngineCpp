#pragma once
#include "Exception.h"
#include "CoreString.h"

namespace DeltaEngine { namespace Core
{
	// http://msdn.microsoft.com/en-us/library/system.exception.aspx
	class CoreLibrary IndexOutOfRangeException : public Exception
	{
	public:
		IndexOutOfRangeException()
			: Exception("IndexOutOfRangeException") {}
	};
}}