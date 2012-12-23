#include "CppUnitTest.h"
#include "CppUnitTestCoreSupport.h"
#include "Core\Object.h"
#include "Core\ArrayHelper.h"
#include <array>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	TEST_CLASS(ArrayHelperTests)
	{
	public:
		TEST_METHOD(Array_Empty)
		{
			auto array = std::array<int, 0>();
			Assert::AreEqual(0U, array.size());
		}

		TEST_METHOD(Array_Constructor)
		{
			auto array = std::array<Object*, 10>();
			Assert::AreEqual(10U, array.size());
		}

		TEST_METHOD(Array_Foreach)
		{
			auto array = std::array<int, 2>();
			array[0] = 2;
			array[1] = 4;
			int sum = 0;
			for (int number : array)
				sum += number;
			Assert::AreEqual(6, sum);
		}

		TEST_METHOD(Array_CloneArray)
		{
			auto array = std::array<Object*, 10>();
			array[1] = &Object();
			array[4] = &Object();
			auto clonedArray = ArrayHelper::Clone(array);
			Assert::AreEqual(10U, clonedArray.size());
			Assert::IsTrue(array[1] == clonedArray[1]);
			Assert::IsTrue(array[4] == clonedArray[4]);
			array = std::array<Object*, 10>();
			Assert::AreEqual(10U, clonedArray.size());
		}

		TEST_METHOD(Array_CloneVector)
		{
			auto array = std::vector<int>(10);
			array[1] = 2;
			array[4] = 4;
			auto clonedArray = ArrayHelper::Clone(array);
			Assert::AreEqual(10U, clonedArray.size());
			Assert::AreEqual(0, clonedArray[0]);
			Assert::AreEqual(2, clonedArray[1]);
			Assert::AreEqual(4, clonedArray[4]);
			array = std::vector<int>(10);
			Assert::AreEqual(10U, clonedArray.size());
		}

		TEST_METHOD(Array_Copy)
		{
			auto array1 = std::array<int, 10>();
			auto array2 = std::array<int, 5>();
			array1[1] = 33;
			std::copy(array1.begin(), array1.begin()+array2.size(), array2.begin());
			Assert::AreEqual(33, array2[1]);
			Assert::AreEqual(5U, array2.size());
		}

		TEST_METHOD(Array_CopyToVector)
		{
			auto array1 = std::array<int, 10>();
			array1[1] = 13;
			auto array2 = std::vector<int>(5);
			std::copy(array1.begin(), array1.begin()+array2.size(), array2.begin());
			Assert::AreEqual(13, array2[1]);
			Assert::AreEqual(5U, array2.size());
		}

		TEST_METHOD(Array_IndexOf)
		{
			auto array = std::array<int, 5>();
			for (int number = 0; number < (int)array.size(); number++)
				array[number] = number;
			Assert::AreEqual(3, ArrayHelper::IndexOf(array, 3));
			Assert::AreEqual(-1, ArrayHelper::IndexOf(array, 6));
		}

		TEST_METHOD(Array_Index)
		{
			auto array = std::array<int, 5>();
			for (int number = 0; number < (int)array.size(); number++)
				array[number] = number;
			Assert::AreEqual(3, ArrayHelper::IndexOf(array, 3));
			for (int& number : array)
				number *= 2;
			Assert::AreEqual(3, ArrayHelper::IndexOf(array, 6));
		}

		TEST_METHOD(Array_ContainsWithNumbers)
		{
			int nativeNumbers[3] = { 1, 2, 5};
			Assert::IsTrue(ArrayHelper::Contains(nativeNumbers, 3, 1));
			Assert::IsFalse(ArrayHelper::Contains(nativeNumbers, 3, 3));
		}

		TEST_METHOD(Array_ContainsWithStdArray)
		{
			std::array<int,3> stdNumbers;
			for (int i = 0; i < 3; i++)
				stdNumbers[i] = i;
			Assert::IsTrue(ArrayHelper::Contains(stdNumbers, 1));
			Assert::IsFalse(ArrayHelper::Contains(stdNumbers, 3));
		}

		TEST_METHOD(Array_ContainsWithObjects)
		{
			auto array = std::array<Object*, 3>();
			auto obj1 = new Object();
			auto obj2 = new Object();
			array[0] = obj1;
			Assert::IsTrue(ArrayHelper::Contains(array, obj1));
			Assert::IsFalse(ArrayHelper::Contains(array, obj2));

			delete obj1;
			delete obj2;
		}

		TEST_METHOD(Array_ToText)
		{
			char* nativeTexts[3] = { "Hi", "there", "whats up" };
			AreEqual("Hi, there, whats up", ArrayHelper::ToText(nativeTexts, 3));
		}

		TEST_METHOD(Array_ToTextWithStdArray)
		{
			std::array<char*,3> stdTexts;
			for (int i=0; i<3; i++)
				stdTexts[i] = "yo";
			AreEqual("yo, yo, yo", ArrayHelper::ToText(stdTexts));
		}

		TEST_METHOD(Array_ToTextWithObjects)
		{
			char* nativeTexts[3] = { "1", "2", "3" };
			auto array = std::array<String, 3>();
			for (int i = 0; i < 3; i++)
				array[i] = String(nativeTexts[i]);
			AreEqual("1, 2, 3", ArrayHelper::ToText(array));
		}
	};
}}}