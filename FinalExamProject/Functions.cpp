#include "Header.h"

void readClassCSV(ifstream& classList, Student& student) // Assume storing student as doubly linked list
{
    // Temp function only read one row for a single student
    string temp;
    // Read the Data from the file as String Vector
    getline(classList, temp, ',');
    student.no = stoi(temp);
    getline(classList, temp, ',');
    student.ID = stoi(temp);
    getline(classList, temp, ',');
    student.firstName = temp;
    getline(classList, temp, ',');
    student.lastName = temp;
    getline(classList, temp, ',');
    student.gender = temp;
    getline(classList, temp, ',');
    student.dateOfBirth = temp;
    getline(classList, temp);
    student.socialID = temp;
}

