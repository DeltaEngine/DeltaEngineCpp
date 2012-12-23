#include "CppUnitTest.h"
#include "CppUnitTestCoreSupport.h"
#include "Core/IEnumerator.h"
#include "Core/IEnumerable.h"
#include "Core/CoreString.h"
#include <vector>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeltaEngine { namespace Core { namespace Tests
{
	class Names : public virtual IEnumerable<String>
	{
	public:
		Names(const std::vector<String> people)
			: people(people) {}

		std::shared_ptr<IEnumerator<String>> GetEnumerator() const
		{
			return std::make_shared<NamesEnumerator>(people);
		}

		class NamesEnumerator : public IEnumerator<String>
		{
		public:
			NamesEnumerator(const std::vector<String> names)
				: names(names)
			{
				position = -1;
			}

			bool MoveNext()
			{
				position++;
				return position < (int)names.size();
			}

			void Reset()
			{
				position = -1;
			}

			String GetCurrent() const
			{
				return names[position];
			}

		private:
			const std::vector<String> names;
			int position;
		};

	private:
		const std::vector<String> people;
	};

	TEST_CLASS(EnumeratorTests)
	{
	public:
		TEST_METHOD(Enumerator_GoingThroughNames)
		{
			std::vector<String> people(3);
			people[0] = String("Rico");
			people[1] = String("Phil");
			people[2] = String("Ben");
			auto names = new Names(people);
			auto enumerator = names->GetEnumerator();
			Assert::IsTrue(enumerator->MoveNext());
			Assert::AreEqual(String("Rico"), enumerator->GetCurrent());
			Assert::IsTrue(enumerator->MoveNext());
			Assert::AreEqual(String("Phil"), enumerator->GetCurrent());
			Assert::IsTrue(enumerator->MoveNext());
			Assert::AreEqual(String("Ben"), enumerator->GetCurrent());
			Assert::IsFalse(enumerator->MoveNext());
			delete names;
		}
	};
}}}