#include "CppUnitTest.h"
#include "CppUnitTestCoreSupport.h"
#include "Core\List.h"
#include "Core\ArrayHelper.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	TEST_CLASS(ListTests)
	{
	public:
		TEST_METHOD(List_Empty)
		{
			auto list = List<float>();
			Assert::IsTrue(0 == list.GetCount());
		}

		TEST_METHOD(List_Add)
		{
			auto list = List<int>();
			list.Add(2);
			list.Add(4);
			Assert::AreEqual(2, list.GetCount());
			Assert::AreEqual(2, list[0]);
			Assert::AreEqual(4, list[1]);
		}

		TEST_METHOD(List_ReferenceCopyWithStdVectorPointer)
		{
			auto list = new std::vector<int>();
			list->push_back(11);
			Assert::AreEqual(1U, list->size());
			auto reference = list;
			Assert::AreEqual(1U, reference->size());
			Assert::AreEqual(11, (*reference)[0]);
			list->push_back(33);
			reference->push_back(55);
			Assert::AreEqual(3U, list->size());
			Assert::AreEqual(3U, reference->size());
			Assert::AreEqual(33, (*reference)[1]);
			Assert::AreEqual(55, (*list)[2]);
			delete list;
		}

		TEST_METHOD(List_Reference)
		{
			auto list = List<int>();
			list.Add(11);
			Assert::AreEqual(1, list.GetCount());
			auto reference = &list;
			Assert::AreEqual(1, reference->GetCount());
			Assert::AreEqual(11, (*reference)[0]);
			list.Add(33);
			Assert::AreEqual(2, list.GetCount());
			Assert::AreEqual(2, reference->GetCount());
			Assert::AreEqual(33, (*reference)[1]);
		}

		TEST_METHOD(List_Clone)
		{
			auto list = List<int>();
			list.Add(11);
			Assert::AreEqual(1, list.GetCount());
			auto clonedList = list;
			Assert::AreEqual(1, clonedList.GetCount());
			clonedList.Add(22);
			Assert::AreEqual(11, clonedList[0]);
			Assert::AreEqual(22, clonedList[1]);
			Assert::AreEqual(1, list.GetCount());
		}

		TEST_METHOD(List_Foreach)
		{
			auto list = List<int>();
			list.Add(2);
			list.Add(4);
			int sum = 0;
			for (int number : list)
				sum += number;
			Assert::AreEqual(6, sum);
		}

		TEST_METHOD(List_Insert)
		{
			auto list = List<int>();
			list.Add(2);
			list.Add(4);
			list.Insert(1, 0);
			list.Insert(3, 2);
			Assert::AreEqual(4, list.GetCount());
			Assert::AreEqual(1, list[0]);
			Assert::AreEqual(2, list[1]);
			Assert::AreEqual(3, list[2]);
			Assert::AreEqual(4, list[3]);
		}

		TEST_METHOD(List_Remove)
		{
			auto list = List<int>();
			list.Add(2);
			list.Add(4);
			list.Remove(2);
			Assert::AreEqual(1, list.GetCount());
			Assert::AreEqual(4, list[0]);
		}

		TEST_METHOD(List_Clear)
		{
			auto list = List<int>();
			list.Add(2);
			list.Add(4);
			list.Clear();
			Assert::AreEqual(0, list.GetCount());
		}

		TEST_METHOD(List_Contains)
		{
			auto list = List<int>();
			list.Add(2);
			list.Add(4);
			Assert::AreEqual(2, list.GetCount());
			Assert::IsTrue(list.Contains(2));
			Assert::IsFalse(list.Contains(3));
		}

		TEST_METHOD(List_ContainsWithStrings)
		{
			auto list = List<String>();
			list.Add(String("Hi"));
			list.Add(String("Ho"));			
			Assert::AreEqual(2, list.GetCount());
			Assert::IsTrue(list.Contains(String("Hi")));
			Assert::IsFalse(list.Contains(String("Ha")));
		}

		TEST_METHOD(List_Iterate)
		{
			auto list = List<char>();
			int count = 0;
			list.Add(1);
			list.Add(3);
			for (char value : list)
				count++;

			Assert::AreEqual(2, count);
		}

		TEST_METHOD(List_ToText)
		{
			auto list = List<String>();
			list.Add("One");
			list.Add("Two");
			list.Add("Three");
			AreEqual("One, Two, Three", list.ToText());
		}

		TEST_METHOD(List_ToArray)
		{
			auto list = List<String>();
			list.Add("One");
			list.Add("Two");
			list.Add("Three");

			auto strings = ArrayHelper::Clone(list);
			Assert::AreEqual(3U, strings.size());
			AreEqual(strings[0], "One");
			AreEqual(strings[1], "Two");
			AreEqual(strings[2], "Three");
		}

		TEST_METHOD(List_WithTypes)
		{
			auto list = List<String>();
			list.Add(typeid(int).name());
			list.Add(typeid(List<String>).name());
			list.Add(typeid(this).name());
			list.Add(typeid(1).name());
			AreEqual("int", list[0]);
			AreEqual("class DeltaEngine::Core::List<class DeltaEngine::Core::String>", list[1]);
			AreEqual("class DeltaEngine::Core::Tests::ListTests *", list[2]);
			Assert::AreEqual(list[0], list[3]);
		}
	};
}}}