#pragma once
#include <cstring>

namespace DeltaEngine { namespace Core
{
	// Useful native string (not std::string) helper methods to work with char*
	class StringHelper final
	{
	public:
		static bool Contains(const char* textToSearch, const char* textToLookFor)
		{
			return strstr(textToSearch, textToLookFor) != NULL;
		}

		static bool AreEqual(const char* text1, const char* text2)
		{
			return strcmp(text1, text2) == 0;
		}
	};
}}