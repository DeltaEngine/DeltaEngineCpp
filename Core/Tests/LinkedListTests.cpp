#include "CppUnitTest.h"
#include <list>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	TEST_CLASS(LinkedListTests)
	{
	public:
		TEST_METHOD(LinkedList_Empty)
		{
			auto list = std::list<float>();
			Assert::AreEqual(0U, list.size());
		}

		TEST_METHOD(LinkedList_Add)
		{
			auto list = std::list<int>();
			int int1 = 2;
			int int2 = 4;
			list.push_back(int1);
			list.push_back(int2);
			Assert::AreEqual(2U, list.size());
			Assert::AreEqual(2, list.front());
			Assert::AreEqual(4, *next(list.begin()));
		}

		TEST_METHOD(LinkedList_Clear)
		{
			auto list = std::list<int>();
			list.push_back(2);
			list.push_back(4);
			list.clear();
			Assert::AreEqual(0U, list.size());
		}

		TEST_METHOD(LinkedList_Iterate)
		{
			auto list = std::list<int>();
			int int1 = 2;
			int int2 = 4;
			int count = 0;
			list.push_back(int1);
			list.push_back(int2);
			auto node = list.begin();
			while (node != list.end())
			{
				node++;
				count++;
			}

			Assert::AreEqual(2, count);
		}
	};
}}}