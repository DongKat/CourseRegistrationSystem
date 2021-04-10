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

void createStudent(ifstream& classList, Students& student) // Read CSV file for student's info
{
	// Temp function only read one row for a single student
	string temp;
	// Read the Data from the file as String Vector
	// Ignore first line
	getline(classList, temp);

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

	getline(classList, temp, '/');
	student.dateOfBirth.day = stoi(temp);
	getline(classList, temp, '/');
	student.dateOfBirth.month = stoi(temp);
	getline(classList, temp, ',');
	student.dateOfBirth.year = stoi(temp);

	getline(classList, temp);
	student.idSocial = temp;
}

void createStudentList(Students*& pHead, string csvFileName)
{
	ifstream file(csvFileName);
	Students* pCur = nullptr;
	while (!file.eof())
	{
		if (pHead == nullptr)
		{
			pHead = new Students;
			pCur = pHead;
			pCur->prev = nullptr;
		}
		else
		{
			pCur->next = new Students;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		pCur = readClassCSV(file, pCur);
		pCur->next = nullptr;
	}
	file.close();
}

void exportCourseStudent(CoursesStudent Course)
{
	ofstream file(Course.courseName + "_List_of_Students.csv");
	string colName[] = { "No", "Student ID", "Student Full Name", "Total Mark", "Final Mark", "Midterm Mark", "Other Mark" };
	for (int i = 0; i < 7; i++)
		file << colName[i] << ",";
	file << endl;
	for (int i = 0; i < sizeof(Course.studentList) / sizeof(Course.studentList[0]); ++i)
	{
		file << i + 1 << ",";
		file << Course.studentList[i].ID << ",";
		file << Course.studentList[i].lastName << Course.studentList[i].firstName << ",";
		file << "," << "," << "," << "," << endl;
	}
}