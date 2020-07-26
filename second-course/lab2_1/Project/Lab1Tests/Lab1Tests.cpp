#include "CppUnitTest.h"
#include "../lab1/map.h"
#include <stdexcept>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab1Tests
{
	TEST_CLASS(Lab1Tests)
	{
	private:
		map<int, int> card;
		List<int> list;
	public:
		TEST_METHOD(insert_test)
		{
			bool before = card.find(5);
			card.insert(5, 1);
			bool after = card.find(5);
			Assert::AreEqual(!before, after);
		}
		TEST_METHOD(remove_test)
		{
			card.insert(5, 1);
			bool before = card.find(5);
			card.remove(5);
			bool after = card.find(5);
			Assert::AreEqual(before, !after);
		}
		TEST_METHOD(remove_wrong_index_text)
		{
			card.insert(5, 1);
			card.insert(6, 2);
			card.insert(7, 3);
			try
			{
				card.remove(8);
			}
			catch (const std::exception &ex)
			{
				Assert::AreEqual(ex.what(), "There is no element in the tree");
			}
		}
		TEST_METHOD(clear_test)
		{
			card.insert(5, 1);
			card.insert(6, 2);
			card.clear();
			Assert::AreEqual(!card.find(5), !card.find(6));
		}
		TEST_METHOD(clear_empty_map_test)
		{
			try
			{
				card.clear();
			}
			catch (const std::exception& ex)
			{
				Assert::AreEqual(ex.what(), "There is no elements in the tree");
			}
		}
		TEST_METHOD(find_test)
		{
			bool before = card.find(5);
			card.insert(5, 1);
			bool after = card.find(5);
			Assert::AreEqual(!before, after);
		}
		TEST_METHOD(get_keys_test)
		{
			card.insert(5, 1);
			card.insert(6, 2);
			card.insert(7, 3);
			list = card.get_keys();
			int sum_of_keys = 0;
			while (!list.isEmpty())
				sum_of_keys += list.next();
			Assert::IsTrue(sum_of_keys == 18);
		}
		TEST_METHOD(get_values_test)
		{
			card.insert(5, 1);
			card.insert(6, 2);
			card.insert(7, 3);
			list = card.get_values();
			int sum_of_values = 0;
			while (!list.isEmpty())
				sum_of_values += list.next();
			Assert::IsTrue(sum_of_values == 6);
		}
	};
}
