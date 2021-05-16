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

void deleteMarks(CourseScore*& pHead)
{
	while (pHead)
	{
		CourseScore* temp = pHead;
		pHead = pHead->next;
	}
}

string checkStudentClass(string studentID) // check if student in a class with allStudents.csv and return class name
{
	ifstream classList, studentList;
	string className, student;
	classList.open(Schoolyear + "/Classes/allClasses.csv");
	while (classList.peek() != EOF)
	{
		getline(classList, className);
		studentList.open(Schoolyear + "/Classes/" + className + "/allStudents.csv");
		while (studentList.peek() != EOF)
		{
			getline(studentList, student);
			if (student == studentID)
				return className;
		}
	}
	return "-1";
}

void exportCourseStudent(ifstream& file)
{
	// copy course scoreboard to outside file
	string line;
	ofstream target("Scoreboard.csv");
	target << "No,StudentID,FullName,Midterm,Final,Bonus,Total\n";
	getline(file, line);
	while (file.peek() != EOF)
	{
		getline(file, line, ',');
		target << line << ',';	// No
		getline(file, line, ',');
		target << line << ',';	// StudentID
		getline(file, line, ',');
		target << line << ' ';	// firstname
		getline(file, line, ',');
		target << line << ',' << endl;	// lastname
		getline(file, line);
		// ignore non-existent scores -1,-1,-1,-1
	}
}

void importScoreboardCourse(ifstream& f, string courseID)
{
	string course_dir = "./" + Schoolyear + "/Semesters/" + Sem + "/" + courseID + "/Scoreboard.csv";
	string tempDir = "./" + Schoolyear + "/Semesters/" + Sem + "/" + courseID + "/Scoreboard_new.csv";
	string temp, mica;

	ifstream courseScoreboard;
	ofstream tempScoreboard;
	courseScoreboard.open(course_dir);
	tempScoreboard.open(tempDir);

	if (!courseScoreboard.is_open())
		throw  std::runtime_error("Can't open course scoreboard");

	getline(f, temp);	// Ignore first line
	getline(courseScoreboard, mica);
	tempScoreboard << mica << endl;

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
		getline(f, temp);	// Total
		tempScore->Total = stof(temp);

		getline(courseScoreboard, mica, ',');	// No
		tempScoreboard << mica << ',';
		getline(courseScoreboard, mica, ',');	// StudentID
		tempScoreboard << mica << ',';
		getline(courseScoreboard, mica, ',');	// First Name
		tempScoreboard << mica << ',';
		getline(courseScoreboard, mica, ',');	// Last Name
		tempScoreboard << mica << ',';
		getline(courseScoreboard, mica);
		tempScoreboard << tempScore->Midterm << ',' << tempScore->Final << ',' << tempScore->Bonus << ',' << tempScore->Total << endl;
		delete tempScore;
	}
	courseScoreboard.close();
	tempScoreboard.close();
	remove(course_dir.c_str());
	rename(tempDir.c_str(), course_dir.c_str());
}

void importScoreboardStudent(ifstream& f, string courseID)
{
	string line, temp;

	ofstream studentScoreboard;

	getline(f, line);	// Ignore first line
	while (f.peek() != EOF)
	{
		getline(f, line);
		stringstream s(line);
		getline(s, temp, ','); // Get No
		getline(s, temp, ','); // Get studentID
		string className = checkStudentClass(temp);
		if (className == "-1")
		{
			continue;
		}
		else
		{
			string dir = Schoolyear + "/Classes/" + className + "/" + temp + "/Course " + Sem + " Scoreboard.csv";
			studentScoreboard.open(dir, ios::app);
			studentScoreboard << courseID << ",";
			getline(s, temp, ','); // Skip name
			getline(s, temp);
			studentScoreboard << temp << endl;
			studentScoreboard.close();
		}
	}
}

void viewCourseScoreboard(ifstream& f)
{
	// view Course scoreboard
	string temp;
	getline(f, temp);	// ignore first line
	int pos = 23;
	gotoxy(8, pos); cout << "No";
	gotoxy(15, pos); cout << "Student ID";
	gotoxy(27, pos); cout << "First Name";
	gotoxy(57, pos); cout << "Last Name";
	gotoxy(71, pos); cout << "Midterm";
	gotoxy(82, pos); cout << "Final";
	gotoxy(92, pos); cout << "Bonus";
	gotoxy(102, pos); cout << "Total";
	pos++;
	while (f.peek() != EOF)
	{
		getline(f, temp, ',');	gotoxy(8, pos);		cout << temp;// no
		getline(f, temp, ',');	gotoxy(15, pos);	cout << temp;
		getline(f, temp, ',');	gotoxy(27, pos);	cout << temp;
		getline(f, temp, ',');	gotoxy(57, pos);	cout << temp;
		getline(f, temp, ',');	gotoxy(71, pos);	cout << temp;
		getline(f, temp, ',');	gotoxy(82, pos);	cout << temp;
		getline(f, temp, ',');	gotoxy(92, pos);	cout << temp;// Total
		getline(f, temp);		gotoxy(102, pos);	cout << temp;
		pos++;
	}
}

void viewOwnScoreboard(ifstream& f, int pos)
{
	string temp;

	while (f.peek() != EOF)
	{
		getline(f, temp, ','); 	gotoxy(50, pos);	cout << temp; // Course ID
		getline(f, temp, ',');	gotoxy(65, pos);	cout << temp; // Midterm
		getline(f, temp, ',');	gotoxy(80, pos);	cout << temp; // Final
		getline(f, temp, ',');	gotoxy(95, pos);	cout << temp; // Bonus
		getline(f, temp);		gotoxy(110, pos);	cout << temp; // Total
		pos++;
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
	if (course_count == 0)
		return sem_gpa;
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
	Nocursortype();
	string studentID;
	string line, temp;
	ifstream studentScoreboard;
	ifstream studentProfile;

	int student_count = 1;

	int pos = 23;
	gotoxy(8, pos); cout << "No";
	gotoxy(15, pos); cout << "Student ID";
	gotoxy(27, pos); cout << "Full Name";
	gotoxy(57, pos); cout << "Course ID";
	gotoxy(71, pos); cout << "Midterm";
	gotoxy(82, pos); cout << "Final";
	gotoxy(92, pos); cout << "Bonus";
	gotoxy(102, pos); cout << "Total";

	pos++;
	while (f.peek() != EOF)
	{
		getline(f, studentID);

		gotoxy(8, pos); cout << student_count++;
		gotoxy(15, pos); cout << studentID;

		studentScoreboard.open(Schoolyear + "/Classes/" + className + "/" + studentID + "/Course " + Sem + " Scoreboard.csv");
		studentProfile.open(Schoolyear + "/Classes/" + className + "/" + studentID + "/Profile.txt");

		getline(studentProfile, temp);
		getline(studentProfile, temp);
		getline(studentProfile, temp);	//get last name
		gotoxy(27, pos); cout << temp << " ";
		getline(studentProfile, temp);	//get first name
		cout << temp;

		studentProfile.close();
		
		while (studentScoreboard.peek() != EOF)
		{
			getline(studentScoreboard, temp, ',');	gotoxy(57, pos);	cout << temp; // Course ID
			getline(studentScoreboard, temp, ',');	gotoxy(71, pos);	cout << temp; // Midterm
			getline(studentScoreboard, temp, ',');	gotoxy(82, pos);	cout << temp; // Final
			getline(studentScoreboard, temp, ',');	gotoxy(92, pos);	cout << temp; // Bonus
			getline(studentScoreboard, temp);		gotoxy(102, pos);	cout << temp; // Total
			pos++;
		}
		studentScoreboard.close();

		studentScoreboard.open(Schoolyear + "/Classes/" + className + "/" + studentID + "/Course " + Sem + " Scoreboard.csv");
		gotoxy(88, pos); cout << "Semester GPA: " << std::setprecision(3) << getSemGPA(studentScoreboard);
		studentScoreboard.close();

		float overall_GPA = 0;
		for (int i = 1; i <= 3; i++)
		{
			studentScoreboard.open(Schoolyear + "/Classes/" + className + "/" + studentID + "/Course Sem " + to_string(i) + " Scoreboard.csv");
			overall_GPA += getSemGPA(studentScoreboard);
			studentScoreboard.close();
		}
		stringstream a(Sem);
		string t;
		getline(a, t, ' ');
		getline(a, t);
		int k = stoi(t);
		overall_GPA /= k;
		gotoxy(88, ++pos); cout << "Overall GPA:  " << std::setprecision(3) << overall_GPA << endl << endl;
		pos++;
		pos++;
	}
}