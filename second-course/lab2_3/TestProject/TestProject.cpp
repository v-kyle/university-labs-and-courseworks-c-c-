#include "CppUnitTest.h"
#include <fstream>
#include<string>
#include"../Laba3/Matrix.h"
#include"../Laba3/Laba3.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForAlgorithmFloydUorshell
{
	TEST_CLASS(UnitTestForAlgorithmFloydUorshell)
	{
	public:
		TEST_METHOD(Test_Path_is_avaible)
		{
			ifstream stream("C:\\Users\ASUS\\Desktop\\Лабораторная работа №3\\Laba3\\TestProject\\example1.txt");

			List<string>* list_fly = new List<string>();

			string city_Start = "Vladivostok";
			string city_End = "Moscow";

			InputDataFromFile(list_fly, stream);

			Matrix* matrix_floid_uorshell = new Matrix(list_fly);
			string excepted = "The best route for the price: 30.000000\nRoute: Vladivostok -> Saint Petersburg -> Moscow ";

			Assert::AreEqual(matrix_floid_uorshell->getResult(city_Start, city_End), excepted);
		}
		TEST_METHOD(Test_Path_is_not_avaible)
		{
			ifstream stream("C:\\Users\\ASUS\\Desktop\\Лабораторная работа №3\\Laba3\\TestProject\\example2.txt");

			List<string>* list_fly = new List<string>();

			string city_Start = "Sochi";
			string city_End = "Saint Petersburg";

			InputDataFromFile(list_fly, stream);

			Matrix* matrix_floid_uorshell = new Matrix(list_fly);
			string excepted = "This route can't be built, try waiting for the flight schedule for tomorrow!";

			Assert::AreEqual(matrix_floid_uorshell->getResult(city_Start, city_End), excepted);
		}
	};
}
