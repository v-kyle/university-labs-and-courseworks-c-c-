#include "CppUnitTest.h"
#include "../CourseWork/Flow.h"
#include "../CourseWork/Flow.cpp"
#include <fstream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define FILE1 "C:\\Users\\ASUS\\Desktop\\CourseWork\\CourseWorkTests\\test1.txt"
#define FILE2 "C:\\Users\\ASUS\\Desktop\\CourseWork\\CourseWorkTests\\test2.txt"
#define FILE3 "C:\\Users\\ASUS\\Desktop\\CourseWork\\CourseWorkTests\\test3.txt"
#define FILE4 "C:\\Users\\ASUS\\Desktop\\CourseWork\\CourseWorkTests\\test4.txt"
#define FILE5 "C:\\Users\\ASUS\\Desktop\\CourseWork\\CourseWorkTests\\test5.txt"
#define FILE6 "C:\\Users\\ASUS\\Desktop\\CourseWork\\CourseWorkTests\\test6.txt"

namespace UnitTestCourseWork
{
	TEST_CLASS(UnitTestCourseWork)
	{
	public:
		TEST_METHOD(Test_Ñorrect_output)
		{
			ifstream stream(FILE1);
			FlowPushRelabel flow(stream);
			int excepted = 19;
			Assert::AreEqual(flow.maximalFlow(), excepted);
		}
		TEST_METHOD(Test_Exception_entering_empty_character) {
			try {
				ifstream stream(FILE2);
				FlowPushRelabel flow(stream);
			}
			catch (exception& ex) {
				Assert::AreEqual(ex.what(), "Error entering a character in the string or missing a space after it.");
			}
		}
		TEST_METHOD(Test_Exception_entering_the_bandwidth) {
			try {
				ifstream stream(FILE3);
				FlowPushRelabel flow(stream);
			}
			catch (exception& ex) {
				Assert::AreEqual(ex.what(), "Error entering the third character (bandwidth) in the string or the presence of a space after it.");
			}
		}
		TEST_METHOD(Test_Exception_empty_string) {
			try {
				ifstream stream(FILE4);
				FlowPushRelabel flow(stream);
			}
			catch (exception& ex) {
				Assert::AreEqual(ex.what(), "A data-entry error. Check the correctness of the input in the file and correct these errors in the line under the number: 2");
			}
		}
		TEST_METHOD(Test_Exception_there_is_a_path_from_the_vertex_to_itself) {
			try {
				ifstream stream(FILE6);
				FlowPushRelabel flow(stream);
			}
			catch (exception& ex) {
				Assert::AreEqual(ex.what(), "The path from the vertex to itself is impossible in the string under the number: 2");
			}
		}
	};
}
