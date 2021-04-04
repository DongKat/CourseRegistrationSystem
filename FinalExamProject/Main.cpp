#include "Header.h"

int main()
{
	ifstream studentsCSV("Test.csv");
	Student student;
	Student student2;
	readClassCSV(studentsCSV, student);
	readClassCSV(studentsCSV, student2);
	studentsCSV.close();
}