#pragma once
#include "CoreString.h"
#include <array>
#include <vector>

namespace DeltaEngine { namespace Core
{
	// Useful native array extensions to quickly evaluate arrays or print the contents out
	class ArrayHelper final
	{
	public:
		static bool Contains(const int array[], int length, int value)
		{
			for (int i = 0; i < length; i++)
				if (array[i] == value)
					return true;

			return false;
		}

		template <typename Type, size_t Size>
		static bool Contains(const std::array<Type, Size> array, const Type value)
		{
			for (int i = 0; i < Size; i++)
				if (array[i] == value)
					return true;

			return false;
		}

		template <typename Type, size_t Size>
		static void Copy(const std::array<Type, Size> from, std::array<Type, Size> to)
		{
			std::copy(from.begin(), from.end(), to.begin());
		}

		template <typename Type, size_t Size>
		static std::array<Type, Size> Clone(const std::array<Type, Size> arrayToDuplicate)
		{
			auto newArray = std::array<Type, Size>();
			std::copy(arrayToDuplicate.begin(), arrayToDuplicate.end(), newArray.begin());
			return newArray;
		}

		template <typename Type>
		static std::vector<Type> Clone(const std::vector<Type> arrayToDuplicate)
		{
			auto newArray = std::vector<Type>(arrayToDuplicate.size());
			std::copy(arrayToDuplicate.begin(), arrayToDuplicate.end(), newArray.begin());
			return newArray;
		}
		
		template <typename Type, size_t Size>
		static int IndexOf(const std::array<Type, Size> array, const Type& value)
		{
			for (int i = 0; i < (int)array.size(); i++)
				if (array[i] == value)
					return i;

			return -1;
		}

		static String ToText(char** array, int length)
		{
			String ret = "";
			for(int i = 0; i < length; i++)
				ret = ret + (ret != "" ? ", " : "") + array[i];

			return ret;
		}

		template <size_t Size>
		static String ToText(std::array<char*, Size> array)
		{
			String ret = "";
			for(int i = 0; i < Size; i++)
				ret = ret + (ret != "" ? ", " : "") + array[i];

			return ret;
		}

		template <size_t Size>
		static String ToText(std::array<String, Size> array)
		{
			String ret = "";
			for(int i = 0; i < Size; i++)
				ret = ret + (ret != "" ? ", " : "") + array[i];

			return ret;
		}
	};
}}