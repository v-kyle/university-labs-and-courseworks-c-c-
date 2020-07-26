#include <iostream>
#include <fstream>
#include "Flow.h"

int main()
{
	ifstream input("input.txt");
	FlowPushRelabel example(input);
	std::cout << "Максимальный поток: " << example.maximalFlow();
}