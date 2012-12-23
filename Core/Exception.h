#pragma once
#include <typeinfo>
#include <string>
#include "Object.h"

namespace DeltaEngine { namespace Core
{
	class String;

	// http://msdn.microsoft.com/en-us/library/system.exception.aspx
	class CoreLibrary Exception : public virtual Object, public std::exception
	{
	public:
		Exception(const char* message = NULL);
		Exception(const String message);
		virtual String ToString() const;

	private:
		void GrabCallstack();
#pragma warning(disable: 4251)
		std::string callstack;
	};
}}