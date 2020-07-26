#pragma once
#include "CppUnitTest.h"
#include <string>
#include <stdexcept>
#include "../Laba2/Shannon.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(Convertion_input_string_test)
		{
			Shannon example;
			string exampleStr = "Блюдо";
			example.Convertion_input_string(exampleStr);
			Assert::AreEqual(example.input_string, exampleStr);

		}
		TEST_METHOD(getEncodedString_test)
		{
			Shannon example;
			string exampleStr = "Блюдо", outString;
			example.Convertion_input_string(exampleStr);
			List<bool> list = example.getEncodedString();
			string TestString = "000001011011"; // "Блюдо"
			for (size_t i = 0; i < list.get_size(); i++)
			{
				if (list.at(i))
					outString = outString + "1";
				else
					outString = outString + "0";
			}
			Assert::AreEqual(TestString, outString);
		}

		TEST_METHOD(decode_test)
		{
			Shannon example;
			string exampleStr = "Чудеса", outString;
			example.Convertion_input_string(exampleStr);
			List<char> list = example.decode("1011101");	//  "сад"
			string TestString = "сад";
			for (size_t i = 0; i < list.get_size(); ++i)
				outString = outString + list.at(i);
			Assert::AreEqual(TestString, outString);
		}

		TEST_METHOD(convertion_with_empty_string)
		{
			Shannon example;
			string exampleStr = "";
			try
			{
				example.Convertion_input_string(exampleStr);

			}
			catch (const exception &ex)
			{
				Assert::AreEqual("Input string is empty", ex.what());
			}
		}

		TEST_METHOD(decode_with_empty_string)
		{
			Shannon example;
			try
			{
				example.show_on_display();

			}
			catch (const exception& ex)
			{
				Assert::AreEqual("There is no string", ex.what());
			}
		}

		TEST_METHOD(empty_string_in_decode)
		{
			string exampleStr = "";
			Shannon example;
			try
			{
				example.decode(exampleStr);

			}
			catch (const runtime_error error)
			{
				Assert::AreEqual("Input string is empty", error.what());
			}
		}
	};
}