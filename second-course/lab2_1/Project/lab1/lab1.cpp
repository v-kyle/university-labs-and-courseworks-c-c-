#include <iostream>
#include "map.h"
using namespace std;

int main()
{
	map<int, int> map;

	for (int i = 0; i < 10; ++i)
	{
		map.insert(i, 10 - i);
	}

	map.print();

	map.remove(3);

	cout << endl;

	map.print();

	List<int> keys = map.get_keys();
	while (!keys.isEmpty())
	{
		cout << keys.next() << " ";
	}

	cout << endl;

	List<int> values = map.get_values();
	while (!values.isEmpty())
	{
		cout << values.next() << " ";
	}
}