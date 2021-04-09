#include "Functions.h"

void readClassCSV(ifstream& classList, Students& student) // Assume storing student as doubly linked list
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
	student.gender = stoi(temp);
    getline(classList, temp, ',');
    //dateofbirth
    getline(classList, temp);
    student.idSocial = temp;
}
