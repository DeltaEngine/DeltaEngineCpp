#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "Core/Object.h"
#include "Core/Exception.h"
#include "Core/List.h"
#include "Core/KeyValue.h"
#include <unordered_map>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	class HashObject : public virtual Object
	{
	public:
		virtual String ToString() const
		{
			return String::Format("HashObject: %X", GetHashCode());
		}

		virtual unsigned int GetHashCode() const
		{
			return Hash64((long)this);
		}

		unsigned int Hash64(long long value) const
		{
			value = ~value + (value << 18);
			value ^= value >> 31 & (long long) 8589934591LL;
			value *= 21;
			value ^= value >> 11 & (long long) 9007199254740991LL;
			value += value << 6;
			value ^= value >> 22 & 1073741823;

			return (unsigned int)value;
		}
	};

	TEST_CLASS(HashtableTests)
	{
	public:
		TEST_METHOD(Hashtable_Create)
		{
			auto hashtableWithDefaultCapacity = std::unordered_map<int, int>();
			Assert::AreEqual(0U, hashtableWithDefaultCapacity.size());
			Assert::AreEqual(8U, hashtableWithDefaultCapacity.bucket_count());

			auto hashtableWithBigCapacity = std::unordered_map<int, int>();
			hashtableWithBigCapacity.reserve(128);
			Assert::AreEqual(0U, hashtableWithBigCapacity.size());
			Assert::AreEqual(128U, hashtableWithBigCapacity.bucket_count());
		}

		TEST_METHOD(Hashtable_Copy)
		{
			auto hashtable = std::unordered_map<int, int>();
			hashtable[10] = 10 * 10;
			hashtable[30] = 30 * 30;
			Assert::AreEqual(2U, hashtable.size());

			auto copyHashtable = std::unordered_map<int, int>(hashtable);
			Assert::AreEqual(2U, copyHashtable.size());
			Assert::AreEqual(100, copyHashtable[10]);
			Assert::AreEqual(900, copyHashtable[30]);

			hashtable[50] = 50 * 50;
			Assert::AreEqual(3U, hashtable.size());
			Assert::AreEqual(2U, copyHashtable.size());
		}

		TEST_METHOD(Hashtable_Add)
		{
			auto hashtable = std::unordered_map<Object*, Object*>();
			auto obj = &HashObject();
			hashtable[obj] = obj;
			Assert::IsTrue(obj == hashtable[obj]);
		}

		TEST_METHOD(Hashtable_Clear)
		{
			auto hashtable = std::unordered_map<std::shared_ptr<Object>, std::shared_ptr<Object>>();
			auto obj = std::make_shared<HashObject>();
			hashtable[obj] = obj;
			for (int i = 0; i < 16; i++)
			{
				auto o = std::make_shared<HashObject>();
				hashtable[o] = o;
			}

			hashtable.clear();
			Assert::AreEqual(0U, hashtable.size());
			Assert::IsTrue(hashtable.find(obj) == hashtable.end());
		}

		TEST_METHOD(Hashtable_ContainsKey)
		{
			auto hashtable = std::unordered_map<Object*, Object*>();
			auto obj1 = &HashObject();
			hashtable[obj1] = obj1;
			Object* obj3 = obj1;
			Assert::IsTrue(hashtable.find(obj3) != hashtable.end());
			Assert::IsTrue(hashtable.find(obj1) != hashtable.end());
#if DEBUG
			// This will be optimized out in release mode, so we will not get the correct end() result.
			auto unusedObj = &HashObject();
			auto nonexistingItem = hashtable.find(unusedObj);
			Assert::IsTrue(nonexistingItem == hashtable.end());
#endif
		}

		TEST_METHOD(Hashtable_Index)
		{
			auto hashtable = std::unordered_map<Object*, Object*>();
			auto obj = &HashObject();
			hashtable[obj] = obj;
			AreEqual(obj, hashtable[obj]);
		}

		TEST_METHOD(Hashtable_ExpandAndRehash)
		{
			auto hashtable = std::unordered_map<std::shared_ptr<Object>, std::shared_ptr<Object>>();
			auto obj1 = std::make_shared<HashObject>();
			auto obj2 = std::make_shared<HashObject>();
			hashtable[obj1] = obj1;
			for(int i = 0; i < 16; i++)
			{
				auto o = std::make_shared<HashObject>();
				hashtable[o] = o;
			}

			hashtable[obj2] = obj2;
			Assert::AreEqual(18U, hashtable.size());
			AreEqual(obj1, hashtable[obj1]);
			AreEqual(obj2, hashtable[obj2]);
		}

		TEST_METHOD(Hashtable_Iterate)
		{
			auto hashtable = std::unordered_map<std::shared_ptr<Object>, std::shared_ptr<Object>>();
			List<KeyValue> keyValues;
			for(int i = 0; i < 16; i++)
			{
				auto o = std::make_shared<HashObject>();
				hashtable[o] = o;
				keyValues.Add(KeyValue(o.get(), o.get()));
			}

			int counter = 0;
			for (auto& value: hashtable)
			{
				Assert::IsTrue(hashtable.find(value.first) != hashtable.end());
				AreEqual(hashtable[value.first], value.second);;
				AreEqual(keyValues[counter].Value, keyValues[counter].Key);
				counter++;
			}
			Assert::AreEqual(16, counter);
		}

		TEST_METHOD(Hashtable_KeyNotFound)
		{
			auto hashtable = std::unordered_map<Object*, Object*>();
			auto obj = &HashObject();
			Assert::IsTrue(hashtable.find(obj) == hashtable.end());
			Assert::IsNull(hashtable[obj]);
		}
	};
}}}