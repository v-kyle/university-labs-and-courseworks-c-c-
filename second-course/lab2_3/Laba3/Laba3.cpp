#include <iostream>
#include <fstream>
#include <string>
#include "Matrix.h"
using namespace std;

void InputDataFromFile(List<string>* data, ifstream& file)
{
	while (!file.eof())
	{
		string str;
		getline(file, str);
		data->push_back(str);
	}
}

void printInfoSchedule(List<string>* list_fly)
{
	for (int i = 0; i < list_fly->get_size(); ++i)
	{
		cout << list_fly->at(i) << endl;
	}
}

int main() {
	setlocale(LC_ALL, "RUS");
	ifstream stream("input.txt");
	List<string>* list_fly = new List<string>();

	string city_Start;
	string city_End;

	InputDataFromFile(list_fly, stream);

	cout << "Flight schedule: " << endl;
	printInfoSchedule(list_fly);

	cout << "Enter the departure city" << endl;
	getline(cin, city_Start);
	cout << "Enter your arrival city" << endl;
	getline(cin, city_End);
	Matrix* matrix_floid_uorshell = new Matrix(list_fly);
	cout << matrix_floid_uorshell->getResult(city_Start, city_End) << endl;
}


