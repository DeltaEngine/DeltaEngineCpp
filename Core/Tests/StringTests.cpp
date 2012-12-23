#include "CppUnitTest.h"
#include "CppUnitTestCoreSupport.h"
#include "Core\List.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	TEST_CLASS(StringTests)
	{
	public:
		TEST_METHOD(String_Constructor)
		{
			String test1 = "Test";
			String test2(String("Test"));
			String test3("Test");
			String test4(std::string("Test"));
			AreEqual("Test", test1);
			AreEqual("Test", test2);
			AreEqual("Test", test3);
			AreEqual("Test", test4);
		}

		TEST_METHOD(String_ConstructorWidestring)
		{
			String test1(L"Test");
			String test2 = L"Test";
			AreEqual("Test", test1);
			AreEqual("Test", test2);
			Assert::AreEqual(test1, test2);
		}

		TEST_METHOD(String_Indexing)
		{
			String test = "Test";
			Assert::AreEqual('T', test[0]);
			Assert::AreEqual('e', test[1]);
			Assert::AreEqual('s', test[2]);
			Assert::AreEqual('t', test[3]);
		}

		TEST_METHOD(String_Length)
		{
			String test = "Test";
			String banana = "Banana";
			Assert::AreEqual(4, test.GetLength());
			Assert::AreEqual(6, banana.GetLength());
		}

		TEST_METHOD(String_Equals)
		{
			String first = String();
			String second = String("Test");
			String third = "Test";
			Assert::IsTrue(first == "");
			Assert::IsTrue(first != second);
			Assert::IsFalse(first != first);
			Assert::IsTrue(first != "Test");
			Assert::IsFalse(first != "");
			Assert::IsTrue(second == third);
			Assert::IsFalse(second.Equals("T"));
			Assert::IsTrue(second.Equals(third));
		}

		TEST_METHOD(String_Compare)
		{
			String first = "Banana bread";
			String second = "banana Bread";
			Assert::AreEqual(0, String::Compare(first, second, true));
			Assert::AreEqual(-1, String::Compare(first, second));
			Assert::AreEqual(1, String::Compare(second, first));
			Assert::AreEqual(0, String::Compare(first, "banana Bread", true));
			Assert::AreEqual(0, String::Compare("Banana bread", second, true));
			Assert::AreEqual(0, String::Compare(first, "Banana bread"));
			Assert::AreEqual(0, String::Compare("banana Bread", second));
		}

		TEST_METHOD(String_PlusAndEqualsPlus)
		{
			String george = "George";
			String lucas = "Lucas";
			String test = george + " " + lucas;
			AreEqual("George Lucas", test);
			george += " ";
			george += lucas;
			AreEqual("George Lucas", george);
		}

		TEST_METHOD(String_ToCharArray)
		{
			const char* originalCharArray = "abc";
			String originalAsString = originalCharArray;
			AreEqual(originalCharArray, originalAsString);
			Assert::IsTrue(strcmp(originalCharArray, originalAsString.ToCharArray()) == 0);
			Assert::AreEqual('a', originalAsString.ToCharArray()[0]);
		}

		TEST_METHOD(String_ToWString)
		{
			String original = "Hi there";
			Assert::AreEqual(L"Hi there", original.ToWString().c_str());
			Assert::IsTrue(L"Hi there" == original.ToWString());
			Assert::AreEqual(L'H', original.ToWString()[0]);
		}

		TEST_METHOD(String_Substring)
		{
			String original = "George Lucas";
			AreEqual("Lucas", original.Substring(7));
			AreEqual("George", original.Substring(0, 6));
			AreEqual("orge L", original.Substring(2, 6));
		}

		TEST_METHOD(String_StartsWith)
		{
			String first = "testing is smart";
			String second = "test";
			String third = "is";
			Assert::IsTrue(first.StartsWith(second));
			Assert::IsTrue(!first.StartsWith(third));
			Assert::IsTrue(first.StartsWith(third, 8));
			Assert::IsTrue(first.StartsWith(third, 8, 8));
			Assert::IsTrue(first.StartsWith("test"));
			Assert::IsTrue(!first.StartsWith("is"));
			Assert::IsTrue(first.StartsWith("is", 8));
			Assert::IsTrue(first.StartsWith("is", 8, 8));
		}

		TEST_METHOD(String_EndsWith)
		{
			String first = "testing is smart";
			String second = "smart";
			String third = "is";
			Assert::IsTrue(first.EndsWith(second));
			Assert::IsTrue(!first.EndsWith(third));
			Assert::IsTrue(first.EndsWith("smart"));
			Assert::IsTrue(!first.EndsWith("is"));
		}

		TEST_METHOD(String_Contains)
		{
			String first = "testing is smart";
			String second = "is";
			Assert::IsTrue(first.Contains(second));
			Assert::IsTrue(first.Contains("is"));
			Assert::IsTrue(!second.Contains(first));
			Assert::IsTrue(!first.Contains("intelligent"));
		}

		TEST_METHOD(String_IndexOf)
		{
			String original = "George Lucas";
			String lucas = "Lucas";
			Assert::AreEqual(original.IndexOf(lucas), 7);
			Assert::AreEqual(original.IndexOf(lucas, 6), 1);
			Assert::AreEqual(original.IndexOf(lucas, 6, 8), 1);
			Assert::AreEqual(original.IndexOf("Lucas"), 7);
			Assert::AreEqual(original.IndexOf("Lucas", 6), 1);
			Assert::AreEqual(original.IndexOf("Lucas", 6, 8), 1);
		}

		TEST_METHOD(String_LastIndexOf)
		{
			String original = "George Lucas";
			Assert::AreEqual(original.LastIndexOf("e"), 5);
			Assert::AreEqual(original.LastIndexOf("e", 7), 5);
			Assert::AreEqual(original.LastIndexOf("e", 7, 2), 5);
		}

		TEST_METHOD(String_ToUpperAndToLower)
		{
			String original = "This is a test.";
			auto lowered = original.ToLower();
			auto uppered = original.ToUpper();
			AreEqual("this is a test.", lowered);
			AreEqual("THIS IS A TEST.", uppered);
		}

		TEST_METHOD(String_Trim)
		{
			String original = "   This is a test.   ";
			AreEqual("   This is a test.", original.TrimEnd());
			AreEqual("This is a test.   ", original.TrimStart());
			AreEqual("This is a test.", original.Trim());
		}

		TEST_METHOD(String_Insert)
		{
			String original = "George Lucas";
			String insertion = " Jr.";
			String insert2 = "Mr. ";
			AreEqual("George Jr. Lucas", original.Insert(6, insertion));
			AreEqual("Mr. George Lucas", original.Insert(0, insert2));
			AreEqual("Mr. George Lucas", original.Insert(0, "Mr. "));
		}

		TEST_METHOD(String_Join)
		{
			String delimiter = ", ";
			auto list = List<String>();
			list.Add("One");
			list.Add("Two");
			list.Add("Three");
			AreEqual("One, Two, Three", String::Join(", ", list));
			AreEqual("One, Two, Three", String::Join(delimiter, list));
		}					

		TEST_METHOD(String_ToString)
		{
			String test = "Test";
			AreEqual("Test", test.ToString());
		}

		TEST_METHOD(String_FormatPlainText)
		{
			AreEqual("Test 123", String::Format("Test 123"));
			AreEqual("Test 123", String::Format(String("Test 123")));
		}

		TEST_METHOD(String_FormatIntegers)
		{
			String stringFormat = String::Format(String("(%d, %d)"), 3, 4);
			String charFormat = String::Format("(%d, %d)", 3, 4);
			AreEqual("(3, 4)", stringFormat);
			AreEqual("(3, 4)", charFormat);
		}

		TEST_METHOD(String_FormatUnsigned)
		{
			String unsignedFormat = String::Format("(%d, %d)", 3U, 4U) + 5U;
			AreEqual("(3, 4)5", unsignedFormat);
		}

		TEST_METHOD(String_FormatLong)
		{
			String unsignedFormat = String::Format("(%lld, %lld)", 323095823054L, 43592893023535235L);
			AreEqual("(323095823054, 43592893023535235)", unsignedFormat);
		}

		TEST_METHOD(String_FormatFloats)
		{
			AreEqual("3.000000", String::Format("%f", 3.0f));
			AreEqual("3 - 4.000000", String::Format("%g - %f", 3.0f, 4.0f));
			AreEqual("3 - 4.000000", String::Format(String("%g - %f"), 3.0f, 4.0f));
		}

		TEST_METHOD(String_FormatLongString)
		{
			String test = "vsnprintf, _vsnprintf, and _vsnwprintf return the number of characters"
				"written if the number of characters to write is less than or equal to count; if th"
				"e number of characters to write is greater than count, these functions return -1 "
				"indicating that output has been truncated.";
			Assert::AreEqual(test, String::Format(test));
		}

		TEST_METHOD(String_AddingStrings)
		{
			String test = "hi";
			test += String(" there") + "!";
			AreEqual("hi there!", test);
		}

		TEST_METHOD(String_AddingInteger)
		{
			String youAreNumberOne = String("You are number ") + 1 + "!";
			AreEqual("You are number 1!", youAreNumberOne);
		}

		TEST_METHOD(String_AddingFloat)
		{
			String oneHalf = String("1/2 is ") + 0.5f + "!";
			AreEqual("1/2 is 0.500000!", oneHalf);
		}
	};
}}}