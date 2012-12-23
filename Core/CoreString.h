//Note: This is named CoreString.h to avoid String.h to be used in other libraries, which causes
//http://stackoverflow.com/questions/531916/error-c2039-memchr-is-not-a-member-of-global-namespace
#pragma once
#pragma warning(disable: 4251)
#include "Object.h"
#include <string>
#include <list>

namespace DeltaEngine { namespace Core
{
	template <typename Type>
	class List;

	// Unlike .NET we use 8bit char and std:string here by following http://www.utf8everywhere.org/
	class CoreLibrary String : public virtual Object
	{
	public:
		String();
		String(const std::string& other);
		String(const char* other);
		String(const wchar_t* other);
		String operator=(const char* other);
		String operator=(const wchar_t* other);
		bool operator==(const String other) const;
		bool operator==(const char* other) const;

		friend bool operator==(const char* other, const String& self)
		{
			return self.Equals(other);
		};

		bool operator!=(const String& other) const;
		bool operator!=(const char* other) const;
		bool Equals(const String& other) const;
		bool Equals(const char* other) const;
		static int Compare(const String& first, const String& second, bool ignoreCase = false);
		static int Compare(const String& first, const char* second, bool ignoreCase = false);
		static int Compare(const char* first, const String& second, bool ignoreCase = false);
		int CompareTo(const String& other) const;
		int CompareTo(const char* other) const;
		String& operator+=(const String& other);
		String& operator+=(const char* other);
		String operator+(const String& other) const;
		String operator+(const char* other) const;
		String operator+(int other) const;
		String operator+(unsigned int other) const;
		String operator+(short other) const;
		String operator+(unsigned short other) const;
		String operator+(long long other) const;
		String operator+(unsigned long other) const;
		String operator+(float other) const;
		char operator[](int index) const;
		int GetLength() const;
		std::string GetStdString() const;
		bool StartsWith(const String& other, int startIndex = 0, int lenght = -1) const;
		bool StartsWith(const char* other, int startIndex = 0, int lenght = -1) const;
		bool EndsWith(const String& other, int startIndex = -1, int lenght = -1) const;
		bool EndsWith(const char* other, int startIndex = -1, int lenght = -1) const;
		bool Contains(const String& other) const;
		bool Contains(const char* other) const;
		int IndexOf(const String& other, int startIndex = 0, int lenght = -1) const;
		int IndexOf(const char* other, int startIndex = 0, int length = -1) const;
		int LastIndexOf(const String& other, int endIndex = -1, int length = -1) const;
		int LastIndexOf(const char* other, int endIndex = -1, int length = -1) const;
		String ToLower() const;
		String ToUpper() const;
		String Trim() const;
		String TrimStart(char token = ' ') const;
		String TrimEnd(char token = ' ') const;
		String Insert(int pos, const String& other) const;
		String Insert(int pos, const char* other) const;
		String Substring(int startIndex, int lenght = -1) const;
		const char* ToCharArray() const;
		const std::wstring ToWString() const;
		virtual String ToString() const;

		friend std::ostream& operator<<(std::ostream& out, String& target)
		{
			return out << target.ToCharArray();
		}

		static String Format(const char* format, ...);
		static String Format(const String format, ...);
		static String Join(const char* delimiter, const List<String>& list);
		static String Join(const String& delimiter, const List<String>& list);

	private:
		std::string text;

		int FindFirst(const String& other) const;
		int FindFirst(const char* other) const;
		int FindLast(const String& other) const;
		int FindLast(const char* other) const;
		int GetStartIndex(int endIndex, int length) const;
		static String FormatInternal(const char* format, va_list* args);
	};
}}