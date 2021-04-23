#include "Functions.h"

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

void exportCourseStudent(Courses course)
{
	// copy course scoreboard to outside file
	string scoreboard_dir = "./" + Schoolyear + "./Semester/Sem " + Sem + "/" + course.courseID + "/Scoreboard.csv";
	string temp;
	ifstream target(scoreboard_dir);
	ofstream file(course.courseID + "_Scoreboard.csv");
	while (!target.eof())
	{
		getline(target, temp);
		file << temp;
	}
}

void viewCourseScoreboard(Courses course)
{
	// view Course scoreboard
	ifstream file("./" + Schoolyear + "/Semester/Sem" + Sem + "/" + course.courseID + "/Scoreboard.csv");
	string temp;
	while (file.eof())
	{
		getline(file, temp, ',');	cout << temp << " | "; // no
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | "; // Total
		getline(file, temp, ',');	cout << temp;
		cout << endl;
	}
}

void viewStudentScoreboard(Students student)
{
	ifstream file("./" + Schoolyear + "/Classes/" + student.className + "/" + student.ID + "/Course Sem " + Sem + ".csv");
	string temp;
	while (file.eof())
	{
		getline(file, temp, ',');	cout << temp << " | ";		// Course ID
		getline(file, temp, ',');	cout << temp << " | ";		// Course Name
		getline(file, temp, ',');	cout << temp << " | ";		// Midterm
		getline(file, temp, ',');	cout << temp << " | ";		// Final
		getline(file, temp, ',');	cout << temp << " | ";		// Bonus
		getline(file, temp);		cout << temp << endl;		// Total
	}
}

string checkStudentInClass(string studentID)
{
	//trash function
	//return whole directory(class name that students is in)
	string className, sID; // studentID
	ifstream classList("./" + Schoolyear + "/Classes/AllClasses.csv");
	while (!classList.eof())
	{
		getline(classList, className);
		ifstream studentList("./" + Schoolyear + "/Classes/" + className + "/AllStudents.csv");
		while (!studentList.eof())
		{
			getline(studentList, sID);
			if (sID == studentID)
			{
				string dir = "./" + Schoolyear + "/Classes/" + className + "/" + studentID + "/";
				return dir;
			}
		}
	}
}

void importScoreboard(Courses* courseHead, string courseID, Students& student)
{
	CourseScore* pHead = new CourseScore, * pCur = pHead;
	// copy outside file to course scoreboard
	string course_dir = Schoolyear + "./Semester/Sem " + Sem + "/" + courseID + "/Scoreboard.csv";
	string line;
	ifstream file(courseID + "_Scoreboard.csv");
	ofstream courseScoreboard(course_dir);

	getline(file, line);
	courseScoreboard << line;
	while (!file.eof())
	{
		getline(file, line);
		courseScoreboard << endl << line;
	}

	file.close();
	file.open(course_dir);

	string student_dir;
	Courses* CourseCur = courseHead;
	while (CourseCur)
	{
		if (CourseCur->courseID == courseID)
			break;
		CourseCur = CourseCur->next;
	}

	getline(file, line);	//skip field name
	while (!file.eof())
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
}

void deleteMarks(CourseScore*& pHead)
{
	while (pHead)
	{
		CourseScore* temp = pHead;
		pHead = pHead->next;
	}
}

void updateStudentResult(Courses Course, string studentID, Scores newScore)
{
	string oldDir, newDir, temp;
	bool recordFlag = false; // check if student record is update. if updated -> true
	oldDir = "./" + Schoolyear + "/Semester/Sem" + to_string(Course.sem) + "/" + Course.courseID + "/Scoreboard.csv";
	newDir = "./" + Schoolyear + "/Semester/Sem" + to_string(Course.sem) + "/" + Course.courseID + "/Scoreboard_new.csv";
	ifstream oldFile(oldDir);
	ofstream newFile(newDir);
	while (!oldFile.eof())
	{
		if (!recordFlag)
		{
			for (int i = 0; i < 8; i++)
			{
				if (i == 7)
				{
					getline(oldFile, temp);
					newFile << temp << "\n";
				}
				getline(oldFile, temp, ',');
				newFile << temp << ",";
				if (temp == studentID)
				{
					getline(oldFile, temp, ',');
					newFile << temp << ",";
					getline(oldFile, temp, ',');
					newFile << temp << ",";
					newFile << "," << newScore.Total << "," << newScore.Final << "," << newScore.Midterm << "," << newScore.Bonus << "\n";
					getline(oldFile, temp);
					recordFlag = true;
					break;
				}
			}
		}
		else
		{
			getline(oldFile, temp);
			newFile << temp << "\n";
		}
	}
	oldFile.close();
	newFile.close();
	remove(oldDir.c_str());
	rename(newDir.c_str(), oldDir.c_str());
}

void viewClassScoreboard(Classes Class) // Require changing UI
{
	Students* pCur = Class.student;

	string studentID;
	string line, temp;
	float overall_GPA = 0;
	ifstream file;

	int student_count = 1;
	int gpa_count = 0;

	while (pCur)
	{
		cout << "No. " << student_count++ << endl;
		cout << pCur->ID << "\t" << pCur->lastName << " " << pCur->firstName << endl;

		file.open("./" + Schoolyear + "/Classes/" + Class.className + "/" + pCur->ID + "/Course Sem " + Sem + "_Scoreboard.csv");
		while (!file.eof())
		{
			getline(file, line);
			stringstream s(line);

			getline(s, temp, ',');
			cout << temp << "\t";	// print course id
			getline(s, temp, ',');
			cout << temp << "\t";	// print course name
			getline(s, temp, ',');
			cout << temp << "\t";	// print total mark
			overall_GPA += stof(temp);
			gpa_count++;
			getline(s, temp, ',');
			cout << temp << "\t";	// print final
			getline(s, temp, ',');
			cout << temp << "\t";	// print midterm
			getline(s, temp);
			cout << temp << "\n";	// print other mark
		}

		overall_GPA /= gpa_count;
		cout << "Overall GPA of whole semester: " << overall_GPA << endl;
		cout << "Overall GPA: " << pCur->overall_gpa << endl;
		file.close();
		overall_GPA = 0;
		gpa_count = 0;
		cout << "Overall GPA: " << overall_GPA << endl;
		student_count++;
	}
}

time_t timeToUnixTime(date end)
{
	int hour, min, sec;
	hour = min = sec = 0;
	//Assume session starts from 00:00:00
	time_t a = time(0);
	tm* timeinfo = localtime(&a);

	timeinfo->tm_year = end.year - 1900;
	timeinfo->tm_mon = end.month - 1;		//months since January - [0,11]
	timeinfo->tm_mday = end.day;			//day of the month - [1,31]
	timeinfo->tm_hour = hour;			//hours since midnight - [0,23]
	timeinfo->tm_min = min;				//minutes after the hour - [0,59]
	timeinfo->tm_sec = sec;				//seconds after the minute - [0,59]

	a = mktime(timeinfo);

	return a;
}

bool isCourseRegistrationSessionActive(date registerStartDay, date registerEndDay)
{
	time_t now = time(0);
	if (timeToUnixTime(registerStartDay) <= now && now <= timeToUnixTime(registerEndDay))
		return true;
	return false;
}