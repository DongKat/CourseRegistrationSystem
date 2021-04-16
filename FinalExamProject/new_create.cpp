#include "create.h"

using namespace std;

schoolYear* newSchoolYear(int yearStart, int yearEnd) {
	schoolYear* newYear = new schoolYear;
	newYear->yearStart = yearStart;
	newYear->yearEnd = yearEnd;
	newYear->next = 0;
	newYear->prev = 0;
	return newYear;
}

void createSchoolYear(schoolYear *&sYear, int yearStart, int yearEnd) {
	if (!sYear) {
		sYear = newSchoolYear(yearStart, yearEnd);
		return;
	}
	schoolYear* cur = sYear;
	while (cur->next) cur = cur->next;
	cur->next = newSchoolYear(yearStart, yearEnd);
	cur->next->prev = cur;
}

date convertToDay(string Day) {
	date ans = { 0,0,0 };
	ans.day = (Day[0] - '0') * 10 + Day[1] - '0';	// convert day
	ans.month = (Day[3] - '0') * 10 + Day[4] - '0';	// convert month
	for (unsigned int i = 6; i < Day.length(); ++i) {		// convert year
		ans.year *= 10;
		ans.year += Day[i] - '0';
	}
	return ans;
}

Students* newStudent(int no, int ID, string FirstName, string LastName, bool gender, date dateOfBirth, string idSocial) {
	Students* stu = new Students;
	stu->no = no;
	stu->ID = ID;
	stu->firstName = FirstName;
	stu->lastName = LastName;
	stu->gender = gender;
	stu->dateOfBirth = dateOfBirth;
	stu->idSocial = idSocial;
	stu->next = nullptr;
	return stu;
}

Classes* newClass(string filepath, string className) {
	Classes* Class = new Classes;
	Class->next = nullptr;
	Class->student = nullptr;
	Class->className = className;
	ifstream f;
	f.open(filepath);
	Students* stu = nullptr;
	while (!f.eof()) {
		int no, ID;
		string FirstName, LastName;
		bool gender;
		date dateOfBirth;
		string idSocial;

		//get NO
		f >> no;
		f.ignore(1000, ',');
		f.ignore(1000, ' ');

		//get ID
		f >> ID;
		f.ignore(1000, ' ');

		//get name
		getline(f, FirstName, ',');
		f.ignore(1000, ' ');
		getline(f, LastName, ',');
		f.ignore(1000, ' ');

		//get gender
		char c;
		f >> c;
		f.ignore(1000, ',');
		f.ignore(1000, ' ');
		if (c == 'F' || c == 'f') gender = 1; // 1 = female, 0 = male
		else gender = 0;

		//get DoB
		string DOB;
		getline(f, DOB, ',');
		f.ignore(1000, ' ');
		dateOfBirth = convertToDay(DOB);

		//get social ID
		getline(f, idSocial);

		//add to class
		if (Class->student) {
			stu->next = newStudent(no, ID, FirstName, LastName, gender, dateOfBirth, idSocial);
			stu = stu->next;
		}
		else {
			Class->student = newStudent(no, ID, FirstName, LastName, gender, dateOfBirth, idSocial);
			stu = Class->student;
		}
	}
	f.close();
	return Class;
}

void addClass(schoolYear& sYear) {
	cin.ignore(1000, '\n');
	cout << "Please enter class's name: ";
	string Cname;
	getline(cin, Cname);

	cout << "Please enter the path of CSV file: ";
	string filepath;
	getline(cin, filepath);

	if (!sYear.Class) sYear.Class = newClass(filepath, Cname);
	else {
		Classes* Class = sYear.Class;
		while (Class->next) Class = Class->next;
		Class->next = newClass(filepath, Cname);
		Class->next->prev = Class;
	}
}

void deleteStudent(Students*& stu) {
	while (stu) {
		Students* tmp = stu;
		stu = stu->next;
		delete tmp;
	}
}

void deleteClass(Classes*& Class) {
	while (Class) {
		Classes* tmp = Class;
		Class = Class->next;
		delete tmp;
	}
}

Semesters *newSemeseter(int currSem, date begin, date end)
{
	Semesters* newSemeseter = new Semesters;
	newSemeseter -> sem = currSem;
	newSemeseter -> dateStart = begin;
	newSemeseter -> dateEnd = end;

	newSemeseter -> prev = NULL;
	newSemeseter -> next = NULL;

	return newSemeseter;
}

void addSemeseter(Semesters*& semester, int currSem, date begin, date end)
{
	if (!semester)
	{
		semester = newSemeseter(currSem, begin, end);
		return;
	}

	Semesters *curr = semester;
	while (curr -> next)
		curr = curr -> next;

	curr -> next = newSemeseter(currSem, begin, end);
	curr -> next -> prev = curr;
}

Courses *newCourse(int currSem, date begin, date end, string courseName, string courseID, string teacherName, int numCredits, int maxStudent, Schedules schedule)
{
	Courses* newCourse = new Courses;
	newCourse -> sem = currSem;
	newCourse -> dateStart = begin;
	newCourse -> dateEnd = end;
	newCourse -> courseName = courseName;
	newCourse -> teacherName = teacherName;
	newCourse -> numCredits = numCredits;
	newCourse -> maxStudent = maxStudent;
	newCourse -> schedule->day = schedule.day;
	newCourse -> schedule->time = schedule.time;

	newCourse -> prev = NULL;
	newCourse -> next = NULL;
}

void addCourse(Courses *&course, int currSem, date begin, date end, string courseName, string courseID, string teacher_name, int numCredits, int maxStudent, Schedules schedule)
{
	if (!course)
	{
		course = newCourse(currSem, begin,  end, courseName, courseID, teacher_name, numCredits, maxStudent, schedule);
		return;
	}

	Courses *curr = course;
	while (curr -> next)
		curr = curr -> next;

	curr -> next = newCourse(currSem, begin,  end, courseName, courseID, teacher_name, numCredits, maxStudent, schedule);
	curr -> next -> prev = curr;
}