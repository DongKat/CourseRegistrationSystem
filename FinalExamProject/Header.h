#pragma once
#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
	Node* next, * prev;
	int data;
};