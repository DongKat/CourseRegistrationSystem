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
		if (ptem->sem == courseNew.sem)
		{
			for (int j = 0; j < 2; j++)
				if ((ptem->schedule[j].day == courseNew.schedule[j].day) && (ptem->schedule[j].time == courseNew.schedule[j].time))
					return false;
		}
		ptem = ptem->next;
	}
	return true;
};

void enrollACourse(Students& aStudent, Courses& courseNew)
{
	int k = courseNew.sem;
	int count = -1;
	fstream f;
	f.open(Schoolyear + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course " + Sem + ".csv", ios::in);
	string ignore_line;
	if (!f.is_open())
		throw "error";
	while (!f.eof())
	{
		getline(f, ignore_line);
		count++;
	}
	f.close();
	f.open(Schoolyear + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course " + Sem + ".csv", ios::out | ios::in);

	if ((checkSchedule(aStudent, courseNew) == true) && (isCourseRegistrationSessionActive(dateStart, dateEnd) == true) && courseNew.countStudent < courseNew.maxStudent)
		if (count < 5)
		{
			for (int i = 0; i < count; i++)
				getline(f, ignore_line);
			f << courseNew.courseID << "," << courseNew.courseName << ",0,0,0,0," << courseNew.schedule[0].day << "," << courseNew.schedule[0].time << "," << courseNew.schedule[1].day << "," << courseNew.schedule[1].time << endl;
			f.close();
			f.open(Schoolyear + "/Semester/Semester" + to_string(k) + "/" + courseNew.courseID + "Scoreboard.csv", ios::in);
			int count1 = -1;
			if (!f.is_open())
				throw "error";
			while (!f.eof())
			{
				getline(f, ignore_line);
				count1++;
			}
			f.close();
			f.open(Schoolyear + "/Semester/Semester" + to_string(k) + "/" + courseNew.courseID + "Scoreboard.csv", ios::out | ios::in);
			for (int i = 0; i <= count; i++)
				getline(f, ignore_line);
			f << ++count1 << "," << aStudent.ID << "," << aStudent.firstName << "," << aStudent.lastName << ",0,0,0,0" << endl;
			f.close();

			// Insert into student's list of enrolled courses
			BasicCourses* pt = aStudent.courseStudent;
			if (pt == nullptr)
			{
				aStudent.courseStudent = new BasicCourses;
				pt->courseID = courseNew.courseID;
				pt->courseName = courseNew.courseName;
				for (int i = 0; i < 2; i++)
					pt->schedule[i] = courseNew.schedule[i];
				pt->sem = courseNew.sem;
			}
			else
			{
				while (pt->next != nullptr)
					pt = pt->next;
				pt->next->courseID = courseNew.courseID;
				pt->next->courseName = courseNew.courseName;
				for (int i = 0; i < 2; i++)
					pt->next->schedule[i] = courseNew.schedule[i];
				pt->next->sem = courseNew.sem;
				courseNew.studentID->next = nullptr;
			}

			// ch�n student v�o course
			if (courseNew.countStudent == 0)
			{
				courseNew.studentID = new BasicStudents;
				courseNew.studentID->firstName = aStudent.firstName;
				courseNew.studentID->lastName = aStudent.lastName;
				courseNew.studentID->ID = aStudent.ID;
				courseNew.studentID->next = nullptr;
			}
			else
			{
				courseNew.studentID->next = new BasicStudents;
				courseNew.studentID->next->firstName = aStudent.firstName;
				courseNew.studentID->next->lastName = aStudent.lastName;
				courseNew.studentID->next->ID = aStudent.ID;
				courseNew.studentID->next = courseNew.studentID;
			}
			courseNew.countStudent++;
		}
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

	if (aStudent->courseStudent == nullptr)
		return;

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