#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h> 

using namespace std;

struct Node
{
	Node* next, * prev;
	int data;
};

void Nocursortype();
void UnNocursortype();
void gotoxy(int x, int y);
void txtColor(int color);
void setWindowFullSize();
void logo_moodle();
void loginUI();