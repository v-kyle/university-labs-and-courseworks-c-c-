#pragma once
#include "Flow.h"

FlowPushRelabel::~FlowPushRelabel() {
	clear();
}

FlowPushRelabel::FlowPushRelabel(ifstream& file)
{
	setInfo(file);
}

int FlowPushRelabel::maximalFlow() {
	if (vertexCount > 2) {
		for (int i = 0; i < vertexCount; i++)
		{
			if (i == sourceVertex)
				continue;
			excessFlowArray[i] = capacity[sourceVertex][i];
			capacity[i][sourceVertex] += capacity[sourceVertex][i];
		}
		height[sourceVertex] = vertexCount;
		List<int> l;
		int cur;
		int cur_index = 0;
		int old_height;
		for (int i = 0; i < vertexCount; i++)
			if (i != sourceVertex && i != destinationVertex)
				l.push_front(i);
		cur = l.at(0);
		while (cur_index < l.get_size())
		{
			old_height = height[cur];
			discharge(cur);
			if (height[cur] != old_height)
			{
				l.push_front(cur);
				l.remove(++cur_index);
				cur = l.at(0);
				cur_index = 0;
			}
			++cur_index;
			if (cur_index < l.get_size())
				cur = l.at(cur_index);

		}
		return excessFlowArray[destinationVertex];
	}
	else
		return capacity[0][1];
}

void FlowPushRelabel::setInfo(ifstream& file)
{
	Map<char, int>* cardCharNumber = new Map<char, int>();
	vertexCount = 0;
	int str_num = 1;
	while (!file.eof()) {
		string s1;
		getline(file, s1);
		if (s1.size() >= 5) {
			if (!((s1[0] >= 'A' && s1[0] <= 'Z') && (s1[1] == ' ')) || !((s1[2] >= 'A' && s1[2] <= 'Z') && (s1[3] == ' '))) {
				throw std::exception("Error entering a character in the string or missing a space after it.");
			}
			string cur;
			for (int i = 4; i < s1.size(); ++i) {
				if (s1[i] >= '0' && s1[i] <= '9')
					cur += s1[i];
				else {
					throw std::exception("Error entering the third character (bandwidth) in the string or the presence of a space after it.");
				}
			}
			if (!cardCharNumber->find_is(s1[0])) {
				cardCharNumber->insert(s1[0], vertexCount);
				++vertexCount;
			}
			if (!cardCharNumber->find_is(s1[2])) {
				cardCharNumber->insert(s1[2], vertexCount);
				++vertexCount;
			}

		}
		else
		{
			throw std::exception(string(("A data-entry error. Check the correctness of the input in the file and correct these errors in the line under the number: " + to_string(str_num))).c_str());
		}
		++str_num;
	}
	if (cardCharNumber->find_is('S'))
		sourceVertex = cardCharNumber->find('S');
	else {
		throw std::exception("Source is missing");
	}

	if (cardCharNumber->find_is('T'))
		destinationVertex = cardCharNumber->find('T');
	else {
		throw std::exception("Sink is missing");
	}
	file.clear();
	file.seekg(ios::beg);
	excessFlowArray = new int[vertexCount];
	height = new int[vertexCount];
	capacity = new int* [vertexCount];
	for (int i = 0; i < vertexCount; ++i) {
		excessFlowArray[i] = 0;
		height[i] = 0;
	}
	for (int i = 0; i < vertexCount; ++i) {
		capacity[i] = new int[vertexCount];
		for (int j = 0; j < vertexCount; ++j)
			capacity[i][j] = 0;
	}
	str_num = 1;
	while (!file.eof()) {
		string s1;
		int vert1, vert2, cap;
		getline(file, s1);
		vert1 = cardCharNumber->find(s1[0]);
		vert2 = cardCharNumber->find(s1[2]);
		if (vert1 == vert2)
			throw std::exception(string("The path from the vertex to itself is impossible in the string under the number: " + to_string(str_num)).c_str());
		capacity[vert1][vert2] = stoi(s1.substr(4));
		++str_num;
	}
}

void FlowPushRelabel::push(int edge, int vertex)
{
	int interVariable = min(excessFlowArray[edge], capacity[edge][vertex]);
	excessFlowArray[edge] -= interVariable;
	excessFlowArray[vertex] += interVariable;
	capacity[edge][vertex] -= interVariable;
	capacity[vertex][edge] += interVariable;
}

void FlowPushRelabel::lift(int edge)
{
	int min = 2 * vertexCount + 1;

	for (int i = 0; i < vertexCount; i++)
		if (capacity[edge][i] && (height[i] < min))
			min = height[i];
	height[edge] = min + 1;
}

void FlowPushRelabel::clear()
{
	delete[] excessFlowArray;
	delete[] height;
	for (int i = 0; i < vertexCount; ++i)
	{
		delete[] capacity[i];
	}
}

void FlowPushRelabel::discharge(int edge)
{
	int vertex = 0;
	while (excessFlowArray[edge] > 0)
	{
		if (capacity[edge][vertex] && height[edge] == height[vertex] + 1)
		{
			push(edge, vertex);
			vertex = 0;
			continue;
		}
		++vertex;
		if (vertex == vertexCount)
		{
			lift(edge);
			vertex = 0;
		}
	}
}

int FlowPushRelabel::min(int data1, int data2) {
	return data1 > data2 ? data2 : data1;
}