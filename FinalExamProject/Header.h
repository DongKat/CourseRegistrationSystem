#pragma once
#include <iostream>
#include <fstream>

#include <windows.h>
#include <conio.h> 

#include <string>
#include <vector>
#include <sstream>


using namespace std;

struct schoolYear 
{
    int yearStart;
    int yearEnd;
    int semester;
};

struct Course
{
    schoolYear t;
    string courseName;
    string Id;
    string teacher_name;
    int numCredits;
    int maxStudents;
    string days;
    int* sessions = new int[2]; // remember to delete
};

struct Staff {
    string name;
    string password;
};

struct Student 
{
    // No, Student ID, First name, Last name, Gender, Date of Birth, Social ID.
    int ID;
    string password = "a";
    int no;
    string firstName, lastName; // first nama, last name
    string gender; // In case someone is Other gender, we are not homophobia here :)
    string dateOfBirth;
    string socialID;
};

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

void readClassCSV(ifstream& classList, Student& student);

