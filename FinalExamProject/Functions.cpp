#include "Functions.h"

bool isLegalDate(date someday)
{
	stringstream s(Schoolyear);
	string y1, y2;
	getline(s, y1, '-');
	getline(s, y2);

	if (stoi(y1) > someday.year || stoi(y2) < someday.year)
		return false;

	if (true)
	{
		if ((someday.month == 1 || someday.month == 3 || someday.month == 5 || someday.month == 7 || someday.month == 8 || someday.month == 10 || someday.month == 12) && someday.day > 0 && someday.day <= 31)
			return true;
		else
			if (someday.month == 4 || someday.month == 6 || someday.month == 9 || someday.month == 11 && someday.day > 0 && someday.day <= 30)
				return true;
			else
				if (someday.month == 2)
				{
					if ((someday.year % 400 == 0 || (someday.year % 100 != 0 && someday.year % 4 == 0)) && someday.day > 0 && someday.day <= 29)
						return true;
					else if (someday.day > 0 && someday.day <= 28)
						return true;
					else
						return false;
				}
				else
					return false;
	}
	else
		return false;
}

void readClassCSV(ifstream& classList, Students& student)
{
	//trash function
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
	//trash function
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
	//trash function
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

void deleteMarks(CourseScore*& pHead)
{
	while (pHead)
	{
		CourseScore* temp = pHead;
		pHead = pHead->next;
	}
}

string checkStudentClass(string studentID) // check if student in a class with Allstudents.txt and return class name
{
	ifstream classList, studentList;
	string className, student;
	classList.open(Schoolyear + "/Classes/AllClasses.txt");
	while (classList.peek() != EOF)
	{
		getline(classList, className);
		studentList.open(Schoolyear + "/Classes/" + className + "/AllStudents.txt");
		while (studentList.peek() != EOF)
		{
			getline(studentList, student);
			if (student == studentID)
				return className;
		}
	}
	return "-1";
}
/*
void importScoreboard(Courses* courseHead, string courseID, Students& student, ifstream& f)
{
	CourseScore* pHead = new CourseScore, * pCur = pHead;
	// copy outside file to course scoreboard
	string course_dir = Schoolyear + "./Semester/Sem " + Sem + "/" + courseID + "/Scoreboard.csv";
	string line;
	ofstream courseScoreboard(course_dir);

	getline(f, line);
	courseScoreboard << line;
	while (f.peek() != EOF)
	{
		getline(f, line);
		courseScoreboard << endl << line;
	}

	f.close();

	string student_dir;
	Courses* CourseCur = courseHead;
	while (CourseCur)
	{
		if (CourseCur->courseID == courseID)
			break;
		CourseCur = CourseCur->next;
	}

	getline(f, line);	//skip field name
	while (file.peek() != EOF)
	{
		getline(file, line);
		stringstream s(line);
		string temp;
		getline(s, temp, ',');
		getline(s, temp, ',');
		pCur->studentID = temp;
		getline(s, temp, ',');
		pCur->Total = stof(temp);
		getline(s, temp, ',');
		pCur->Final = stof(temp);
		getline(s, temp, ',');
		pCur->Midterm = stof(temp);
		getline(s, temp);
		pCur->Bonus = stof(temp);

		pCur->next = new CourseScore;
		pCur = pCur->next;
	}
	pCur = pHead;
	BasicStudents* StudentCur = CourseCur->studentID;
	while (StudentCur)
	{
		student_dir = "./" + Schoolyear + "/Classes/" + StudentCur->className + "/" + StudentCur->ID + "/Course Sem " + Sem + "_Scoreboard.csv";
		ofstream studentScoreboard(student_dir, ios::out | ios::app);
		while (pCur)
			if (pCur->studentID == StudentCur->ID)
			{
				student.overall_gpa += pCur->Total;
				student.total_courses_count++;
				studentScoreboard << CourseCur->courseID << "," << CourseCur->courseName << "," << pCur->Total << "," << pCur->Final << "," << pCur->Midterm << "," << pCur->Bonus << endl;
				break;
			}
		StudentCur = StudentCur->next;
	}
	delete pHead;
}

*/

void exportCourseStudent(ifstream& file)
{
	// copy course scoreboard to outside file
	string line;
	ofstream target("Scoreboard.csv");
	while (!file.eof())
	{
		getline(file, line, ',');
		target << line << ',';	// No
		getline(file, line, ',');
		target << line << ',';	// StudentID
		getline(file, line, ',');
		target << line << ' ';	// firstname
		getline(file, line, ',');
		target << line << endl;	// lastname
		// ignore non-existent scores -1,-1,-1,-1
	}
}

void importScoreboardCourse(ifstream& f, string courseID)
{
	string course_dir = Schoolyear + "./Semester/Sem " + Sem + "/" + courseID + "/Scoreboard.csv";
	string tempDir = Schoolyear + "./Semester/Sem " + Sem + "/" + courseID + "/Scoreboard_new.csv";
	string temp, mica;

	ifstream courseScoreboard;
	ofstream tempScoreboard;
	courseScoreboard.open(course_dir);
	tempScoreboard.open(tempDir);

	while (f.peek() != EOF)
	{
		Scores* tempScore = new Scores;
		getline(f, temp, ',');	// No
		getline(f, temp, ',');	// StudentID
		getline(f, temp, ',');	// FullName

		getline(f, temp, ',');	// Midterm
		tempScore->Midterm = stof(temp);
		getline(f, temp, ',');	// Final
		tempScore->Final = stof(temp);
		getline(f, temp, ',');	// Bonus
		tempScore->Bonus = stof(temp);
		getline(f, temp, ',');	// Total
		tempScore->Total = stof(temp);

		getline(courseScoreboard, mica, ',');	// No
		tempScoreboard << mica << ',';
		getline(courseScoreboard, mica, ',');	// StudentID
		tempScoreboard << mica << ',';
		getline(courseScoreboard, mica, ',');	// First Name
		tempScoreboard << mica << ',';
		getline(courseScoreboard, mica, ',');	// Last Name
		tempScoreboard << mica << ',';
		tempScoreboard << tempScore->Midterm << tempScore->Final << tempScore->Bonus << tempScore->Total << endl;
		delete tempScore;
	}
	remove(tempDir.c_str());
	rename(tempDir.c_str(), course_dir.c_str());
}

void importScoreboardStudent(ifstream& f, string courseID)
{
	string student_dir, line, temp;

	ofstream studentScoreboard;

	while (f.peek() != EOF)
	{
		getline(f, line);
		stringstream s(line);
		getline(s, temp, ','); // Get studentID
		string className = checkStudentClass(temp);
		if (className == "-1")
		{
			continue;
		}
		else
		{
			studentScoreboard.open(Schoolyear + "/Classes/" + className + "/" + temp + "/Course " + Sem + " Scoreboard.csv", ios::app | ios::out);
			studentScoreboard << courseID << ",";
			getline(s, temp);
			studentScoreboard << temp;
			studentScoreboard.close();
		}
	}
}

void viewCourseScoreboard(ifstream& f)
{
	// view Course scoreboard
	string temp;
	int tmp = 21;
	getline(f, temp);
	while (f.peek() != EOF)
	{
		gotoxy(20, tmp);
		getline(f, temp, ',');	cout << temp << "\t\t"; // no
		getline(f, temp, ',');	cout << temp << "\t\t";
		getline(f, temp, ',');	cout << temp << "\t\t";
		getline(f, temp, ',');	cout << temp << "\t\t";
		getline(f, temp, ',');	cout << temp << "\t\t";
		getline(f, temp, ',');	cout << temp << "\t\t";
		getline(f, temp, ',');	cout << temp << "\t\t"; // Total
		getline(f, temp);		cout << temp;
		tmp++;
	}
}

void viewOwnScoreboard(ifstream& f, int pos)
{
	string temp;

	while (f.peek() != EOF)
	{
		getline(f, temp, ','); 	cout << temp << "\t"; // Course ID
		getline(f, temp, ',');	cout << temp << "\t"; // Midterm
		getline(f, temp, ',');	cout << temp << "\t"; // Final
		getline(f, temp, ',');	cout << temp << "\t"; // Bonus
		getline(f, temp);		cout << temp << "\t"; // Total
	}
}

float getSemGPA(ifstream& f)
{
	string temp;
	float sem_gpa = 0;
	int course_count = 0;
	while (f.peek() != EOF)
	{
		getline(f, temp, ',');
		getline(f, temp, ',');
		getline(f, temp, ',');
		getline(f, temp, ',');
		getline(f, temp);
		sem_gpa += stof(temp);
		course_count++;
	}
	sem_gpa /= course_count;
	return sem_gpa;
}

void updateStudentResult(ifstream& f1, ifstream& f2, ofstream& nf1, ofstream& nf2, string studentID, string courseID, Scores newScore)
{
	// check if student record is update. if updated -> true
	bool recordFlag = false;
	string line, temp;

	// Update Course Scoreboard
	while (f1.peek() != EOF)
	{
		getline(f1, line);

		if (!recordFlag)
		{
			stringstream s(line);

			getline(s, temp, ',');	// Read No.
			nf1 << temp << ',';
			getline(s, temp, ',');	// Read StudentID
			nf1 << temp << ',';
			if (temp == studentID)
			{
				recordFlag = true;
				getline(s, temp, ',');	// Read Last Name
				nf1 << temp << ',';
				getline(s, temp, ',');	// Read First Name
				nf1 << temp << ',';
				getline(s, temp);	// Swallow the old score
				nf1 << newScore.Midterm << ',' << newScore.Final << ',' << newScore.Bonus << ',' << newScore.Total << endl;
			}
			else
			{
				getline(s, temp);
				nf1 << temp << endl;
			}
		}
		else
		{
			nf1 << line << endl;
		}
	}

	recordFlag = false; // Reusing variable, optimize memory usage :^)

	while (f2.peek() != EOF)
	{
		getline(f2, line);

		if (!recordFlag)
		{
			stringstream s(line);

			getline(s, temp, ',');	// Read CourseID
			nf2 << temp << ',';
			if (temp == courseID)
			{
				recordFlag = true;
				getline(s, temp, ',');	// Read Course Name
				nf2 << temp << ',';
				getline(s, temp);	// Swallow the old score
				nf2 << newScore.Midterm << ',' << newScore.Final << ',' << newScore.Bonus << ',' << newScore.Total << endl;
			}
			// In case student ID is not found
			else
			{
				getline(s, temp);
				nf2 << temp << endl;
			}
		}
		// In case certain record is found so get the whole line of the rest
		else
		{
			nf2 << line << endl;
		}
	}
}

void viewClassScoreboard(ifstream& f, string className) // Require changing UI
{
	string studentID;
	string line, temp;
	ifstream studentScoreboard;
	ifstream studentProfile;

	int student_count = 1;

	int pos = 21;

	while (f.peek() != EOF)
	{
		getline(f, studentID);

		cout << "No. " << student_count++ << "\t" << studentID << "\t";

		studentScoreboard.open(Schoolyear + "/Classes/" + className + "/" + studentID + "/Course " + Sem + " Scoreboard.csv");
		studentProfile.open(Schoolyear + "/Classes/" + className + "/" + studentID + "/Profile.txt");

		getline(studentProfile, temp);	//get last name
		cout << temp << "\t";
		getline(studentProfile, temp);	//get first name
		cout << temp << "\n";

		studentProfile.close();

		viewOwnScoreboard(studentScoreboard, pos);

		cout << "Semester GPA: " << getSemGPA(studentScoreboard);
		studentScoreboard.close();

		float overall_GPA = 0;
		for (int i = 1; i <= 3; i++)
		{
			studentScoreboard.open(Schoolyear + "/Classes/" + className + "/" + studentID + "/Course Sem " + to_string(i) + " Scoreboard.csv");
			overall_GPA += getSemGPA(studentScoreboard);
			studentScoreboard.close();
		}
		overall_GPA /= 3;
		cout << "Overall GPA: " << overall_GPA;
		student_count++;
	}
}