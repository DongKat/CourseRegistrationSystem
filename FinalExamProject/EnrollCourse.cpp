#include "Struct.h"
#include "EnrollCourse.h"

time_t timeToUnixTime(date end)
{
	int hour, min, sec;
	hour = min = sec = 0;
	//Assume session starts from 00:00:00
	time_t a = time(0);
	tm* timeinfo = localtime(&a);

	timeinfo->tm_year = end.year - 1900;
	timeinfo->tm_mon = end.month - 1;        //months since January - [0,11]
	timeinfo->tm_mday = end.day;            //day of the month - [1,31]
	timeinfo->tm_hour = hour;            //hours since midnight - [0,23]
	timeinfo->tm_min = min;                //minutes after the hour - [0,59]
	timeinfo->tm_sec = sec;                //seconds after the minute - [0,59]

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

bool checkSchedule(Students aStudent, Courses courseNew)
{
	BasicCourses* ptem = aStudent.courseStudent;
	while (ptem != nullptr)
	{
		for (int j = 0; j < 2; j++)
			if (ptem->schedule[j].day == courseNew.schedule[j].day && ptem->schedule[j].time == courseNew.schedule[j].time)
				return false;
		ptem = ptem->next;
	}
	return true;
};

void enrollACourse(Students& aStudent, Courses& courseNew)
{
	int k = courseNew.sem;
	int count = -1;
	ifstream infile;
	infile.open(Schoolyear + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course " + Sem + ".csv");
	string ignore_line;

	// Check file exist?
	if (!infile.is_open())
		throw std::runtime_error("Oh shit, we messed up. There's no Course Sem file...");
	// Count how many course already enrolled in file
	while (infile.peek() != EOF)
	{
		getline(infile, ignore_line);
		count++;
	}
	infile.close();

	ofstream outfile;

	if (checkSchedule(aStudent, courseNew) && isCourseRegistrationSessionActive(dateStart, dateEnd) && courseNew.countStudent < courseNew.maxStudent)
		if (count < 5)
		{
			// Open Student's course list, add new course to .csv file
			outfile.open(Schoolyear + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course " + Sem + ".csv", ios::out | ios::app);
			outfile << courseNew.courseID << "," << courseNew.courseName << courseNew.schedule[0].day << "," << courseNew.schedule[0].time << "," << courseNew.schedule[1].day << "," << courseNew.schedule[1].time << endl;
			outfile.close();

			// Add Student's name to Course Scoreboard.csv
			outfile.open(Schoolyear + "/Semester/" + Sem + "/" + courseNew.courseID + "Scoreboard.csv", ios::out | ios::app);
			outfile << ++courseNew.countStudent << "," << aStudent.ID << "," << aStudent.firstName << "," << aStudent.lastName << "-1,-1,-1,-1" << endl;
			// default course's scoreboard:
			// Ex: 31,101,Anpan,Suhkoi,-1,-1,-1,-1

			// Insert into student's list of enrolled courses
			BasicCourses* pt = nullptr;
			if (aStudent.courseStudent)
			{
				aStudent.courseStudent = new BasicCourses;
				pt = aStudent.courseStudent;
			}
			else
			{
				while (pt->next != nullptr)
					pt = pt->next;
				pt->next = new BasicCourses;
				pt = pt->next;
			}
			pt->courseID = courseNew.courseID;
			pt->courseName = courseNew.courseName;
			for (int i = 0; i < 2; i++)
				pt->next->schedule[i] = courseNew.schedule[i];
			pt->next = nullptr;

			// Insert Student into Course's students list
			BasicStudents* ps = nullptr;
			if (courseNew.countStudent == 0)
			{
				courseNew.studentID = new BasicStudents;
				ps = courseNew.studentID;
			}
			else
			{
				ps->next = new BasicStudents;
				ps = ps->next;
			}
			courseNew.studentID->next->firstName = aStudent.firstName;
			courseNew.studentID->next->lastName = aStudent.lastName;
			courseNew.studentID->next->ID = aStudent.ID;
			courseNew.studentID->next = courseNew.studentID;
		}
		else
			throw std::runtime_error("Maximum number of courses reached!");
	else
		throw std::runtime_error("New course's schedule conflict with already enrolled ones");
}

void viewEnrolledCourses(Students* aStudent)
{
	string line, temp;

	ifstream file;
	file.open(Schoolyear + "/Classes/" + aStudent->className + "/" + aStudent->ID + "/Course " + Sem + ".csv");

	// Print field Names
	cout << "Course ID\t" << "Course Name\t" << "Teacher Name\t" << "Credits\t" << "Number of students\t" << "Session 1\t" << "Session 2\t";

	while (file.peek() != EOF)
	{
		getline(file, temp, ',');	// Course ID
		cout << temp << "\t";
		getline(file, temp, ',');	// Course Name
		cout << temp << "\t";
		getline(file, temp, ',');	// Teacher
		cout << temp << "\t";
		getline(file, temp, ',');	// Credits
		cout << temp << "\t";
		getline(file, temp, ',');	// NumStudents
		cout << temp << "\t";
		getline(file, temp, ',');	// Weekday 1
		cout << temp << "\t";
		getline(file, temp, ',');	// Period 1
		cout << temp << "\t";
		getline(file, temp, ',');	// Weekday 2
		cout << temp << "\t";
		getline(file, temp);		// Period 2
		cout << temp;
	}
	file.close();
}

void removeACourse(Students* aStudent, Courses* courseDelete)
{
	// How does it work:
	/*
		- Remove BasicStudent node inside Courses
		- Remove BasicCourse node inside Students
		- Pass two linked list to updateCourseB4D
	*/
	// check if course list empty
	if (aStudent->courseStudent == nullptr)
		throw std::runtime_error("You haven't enroll any course yet!");

	ifstream file;
	string ignore_line;

	// Delete student linked list in course
	BasicStudents* pCurStudent = courseDelete->studentID;
	BasicStudents* pDelStudent = nullptr;

	if (courseDelete->studentID->ID == aStudent->ID)
	{
		pDelStudent = courseDelete->studentID;
		courseDelete->studentID = pCurStudent->next;
		delete pDelStudent;
	}
	while (pCurStudent != nullptr && pCurStudent->ID != aStudent->ID)
	{
		pDelStudent = pCurStudent;
		pCurStudent = pCurStudent->next;
	}
	if (pCurStudent == nullptr)
		return;
	pDelStudent->next = pCurStudent->next;
	delete pCurStudent;

	//Delete course in students
	BasicCourses* pCurCourse = aStudent->courseStudent;
	BasicCourses* pDelCourse = nullptr;
	if (aStudent->courseStudent->courseID == courseDelete->courseID)
	{
		pDelCourse = aStudent->courseStudent;
		aStudent->courseStudent = pCurCourse->next;
		delete pDelCourse;
	}
	while (pCurCourse != nullptr && pCurCourse->courseID != courseDelete->courseID)
	{
		pDelCourse = pCurCourse;
		pCurCourse = pCurCourse->next;
	}
	if (pCurCourse == nullptr)
		return;
	pDelCourse->next = pCurCourse->next;
	delete pCurCourse;

	updateCourseB4D(aStudent, courseDelete);
};

void updateCourseB4D(Students* aStudent, Courses* courseDelete)
{
	// How does it work:
	/*
		- Delete Student's "Course Sem X.csv"
		- Create new "Course Sem X.csv";
		- Ouput Enrolled Courses linked list into new "Course Sem X.csv"
		- Repeat same steps for Course's "Scoreboard.csv"
	*/

	ofstream file;

	string dir = "./" + Schoolyear + "/Classes/" + aStudent->className + "/" + aStudent->ID + "/Course " + Sem + ".csv";
	//Example dir: ./2020-2021/Classes/19apcs1/100/Course Sem 1.csv

	remove(dir.c_str());
	file.open(dir);

	BasicCourses* pCurrentCourse = aStudent->courseStudent;
	while (pCurrentCourse != nullptr)
	{
		file << pCurrentCourse->courseID << "," << pCurrentCourse->courseName << "," << courseDelete->schedule[0].day << "," << courseDelete->schedule[0].time << "," << courseDelete->schedule[1].day << "," << courseDelete->schedule[1].time << endl;
		pCurrentCourse = pCurrentCourse->next;
	}
	file.close();

	// Update file in course folder
	dir = "./" + Schoolyear + "/Semester/" + Sem + "/" + courseDelete->courseID + "/Scoreboard.csv";

	remove(dir.c_str());
	file.open(dir);

	BasicStudents* pCurrentStudent = courseDelete->studentID;
	int count = 1;
	while (pCurrentStudent != nullptr)
	{
		file << count++ << "," << pCurrentStudent->ID << "," << pCurrentStudent->firstName << "," << pCurrentStudent->lastName << ",0,0,0,0" << endl;
		pCurrentStudent = pCurrentStudent->next;
	}
	file.close();
}

void viewAllStudentInCourse(Courses* course)
{
	int count = 1;
	BasicStudents* pCur = course->studentID;
	while (pCur != nullptr)
	{
		cout << count++ << "ID: " << pCur->ID << '\t' << "Name: " << pCur->firstName << " " << pCur->lastName;
		pCur = pCur->next;
	}
}

void viewAllStudentInClass(Classes* Class)
{
	int count = 1;
	Students* pCur = Class->student;
	while (pCur != nullptr)
	{
		cout << count++ << "ID: " << pCur->ID << '\t' << "Name: " << pCur->firstName << " " << pCur->lastName;
		pCur = pCur->next;
	}
}

void viewAllCourse()
{
	Courses* curCourse = COURSE;
	while (curCourse != nullptr)
	{
		cout << " Course ID: " << curCourse->courseID << " Course name: " << curCourse->courseName;
		curCourse = curCourse->next;
	}
}