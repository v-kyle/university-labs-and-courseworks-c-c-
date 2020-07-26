#include <iostream>
#include "Shannon.h"


void showInfoAboutString(Shannon& obj, string str)
{
	obj.Convertion_input_string(str);
	obj.show_on_display();
}

int main()
{
	setlocale(0, "Rus");
	Shannon example;
    	showInfoAboutString(example, "Классика – то, что каждый считает нужным прочесть и никто не читает.");
	showInfoAboutString(example, "Плох тот классик, которому ничего не приписывают.");
	showInfoAboutString(example, "Классика — это то, что каждый хотел бы прочесть, по возможности — не читая.");
	system("pause");
}
