#pragma once
#include "CoreString.h"
#include "ICollection.h"
#include "IndexOutOfRangeException.h"
#include <vector>
#include <algorithm>
#include <memory>

namespace DeltaEngine { namespace Core
{
	// http://msdn.microsoft.com/en-us/library/6sh2ey19.aspx
	// Like C# this using a std::vector, not a std::list (which is much slower to access index wise).
	// You are obviously free to use std::vector or std::list or any other type directly as you like.
	template <typename Type>
	class List : public virtual Object, public virtual ICollection<Type>, public std::vector<Type>
	{
	public:
		int GetCount() const
		{
			return size();
		}

		bool GetIsReadOnly() const
		{
			return false;
		}

		void Add(const Type& element)
		{
			push_back(element);
		}

		void Clear()
		{
			clear();
		}

		void CopyTo(Type* array, int arrayIndex = 0) const
		{
			if (arrayIndex < 0)
				throw IndexOutOfRangeException();

			for (int i = 0; i < GetCount(); i++)
				array[i+arrayIndex] = std::vector<Type>::operator[](i);
		}

		List<Type> Reverse() const
		{
			auto reversedList = List<Type>();
			for (int i = GetCount() - 1; i >= 0; i--)
				reversedList.Add(std::vector<Type>::operator[](i));
			return reversedList;
		}

		int IndexOf(const Type& value)
		{
			for (int i = 0; i < GetCount(); i++)
				if (operator[i] == value)
					return i;

			return -1;
		}

		bool Contains(Type element)
		{
			for (Type& elem : *this)
				if (elem == element)
					return true;

			return false;
		}

		void Remove(const Type& element)
		{
			erase(std::remove(begin(), end(), element), end());
		}

		void Insert(const Type& element, int index)
		{
			insert(next(begin(), index), element);
		}

		String ToText() const
		{
			return String::Join(", ", *this);
		}

		std::shared_ptr<IEnumerator<Type>> GetEnumerator() const
		{
			return std::make_shared<ListEnumerator>(begin(), end());
		}

		class ListEnumerator : public IEnumerator<Type>
		{
		public:
			ListEnumerator(typename List<Type>::const_iterator begin,
				typename List<Type>::const_iterator end)
			{
				this->begin = begin;
				this->end = end;
				Reset();
			}

			bool MoveNext()
			{
				bool gotMoreData = current != end;
				if (beginAlreadySet)
					beginAlreadySet = false;
				else if (gotMoreData)
					current++;
				return gotMoreData;
			}

			void Reset()
			{
				current = begin;
				beginAlreadySet = true;
			}

			Type GetCurrent() const
			{
				return *current;
			}

		private:
			typename List<Type>::const_iterator current;
			typename List<Type>::const_iterator begin;
			typename List<Type>::const_iterator end;
			bool beginAlreadySet;
		};

	private:
		// Disable assignment
		List& operator=(List const&) {}
	};
}}