#include "Functions.h"

void readClassCSV(ifstream& classList, Students& student)
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
		readClassCSV(file, *pCur);
		pCur->next = nullptr;
	}
	file.close();
}

void exportCourseStudent(Courses Course)
{
	ofstream file(Course.courseName + "_List_of_Students.csv");
	string colName[] = { "No", "Student ID", "Student Full Name", "Total Mark", "Final Mark", "Midterm Mark", "Other Mark" };
	for (int i = 0; i < 7; i++)
		file << colName[i] << ",";
	file << endl;
	int j = 0;
	while(Course.studentID)
	{
		file << j + 1 << ",";
		file << Course.studentID->ID << ",";
		file << Course.studentID->lastName << Course.studentID->firstName << ",";
		file << "," << "," << "," << "," << endl;
		Course.studentID = Course.studentID->next;

	}
}

void viewScoreboard(Courses Course)
{
	ifstream file("School year/Semester/Sem" + to_string(Course.sem) + "/" + Course.courseID + "/Scoreboard.csv");
	string temp;
	while (file.eof())
	{
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp;
		cout << endl;
	}
}

void importScoreboard(Courses Course)
{
	// I am void, is this neeeded since we are reading files :o
	return;
}

void updateStudentResult(Courses Course, string studentID)
{
	string oldDir, newDir;
	oldDir = "./School year/Semester/Sem" + to_string(Course.sem) + "/" + Course.courseID + "/Scoreboard.csv";
	newDir = "./School year/Semester/Sem" + to_string(Course.sem) + "/" + Course.courseID + "/Scoreboard_new.csv";
	ifstream oldFile(oldDir);
	ofstream newFile(newDir);
	string temp;
	while (!oldFile.eof())
	{
			getline(oldFile, temp,',');
			newFile << temp << ",";
			if (temp == studentID)
			{
				int i;
				cout << "Record found!\n";
				cout << "New midterm score\n";
				cin >> i;
				newFile << i << ",";
				cout << "New final score\n";
				cin >> i;
				newFile << i << ",";
				cout << "New bonus score\n";
				cin >> i;
				newFile << i << ",";
				cout << "New overall score\n";
				cin >> i;
				newFile << i << "\n";
		}
	}
	oldFile.close();
	newFile.close();
	remove(oldDir.c_str());
	rename(newDir.c_str(), oldDir.c_str());
}

void viewClassScoreboard(Courses Course, string className) // ;-;
{
	string studentID;

	ifstream file("School year/Classes/" + className + "/" + studentID + "/Course Sem" + to_string(Course.sem) + ".csv");
	string temp;
	while (file.eof())
	{	
		for(int i = 0; i < 7; i++)
		{
			getline(file, temp, ',');
			cout << temp << " ";
		}
		getline(file, temp);
		cout << temp << endl;
	}
}
