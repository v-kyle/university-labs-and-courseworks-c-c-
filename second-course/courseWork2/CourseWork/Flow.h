#pragma once
#include <fstream>
#include "List.h"
#include <string>
#include"Map.h"

using namespace std;
class FlowPushRelabel {
private:
	#pragma region VARIABLES
	int* excessFlowArray;
	int** capacity;
	int* height;
	int vertexCount, sourceVertex, destinationVertex;
	#pragma endregion

	#pragma region FUNCTIONS
	int min(int, int);
	#pragma endregion
public:
	FlowPushRelabel() = default;
	FlowPushRelabel(ifstream&);
	~FlowPushRelabel();

	int maximalFlow();
	void setInfo(ifstream&);
	void push(int, int);
	void clear();
	void lift(int);
	void discharge(int);
};