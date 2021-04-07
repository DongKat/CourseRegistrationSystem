#include "create.h"

using namespace std;

schoolYear* newSchoolYear(int yearStart, int yearEnd) {
	schoolYear* newYear = new schoolYear;
	newYear->yearStart = yearStart;
	newYear->yearEnd = yearEnd;
	newYear->Class = 0;
	newYear->next = 0;
	newYear->prev = 0;
	return newYear;
}

void createSchoolYear(schoolYear*& sYear, int yearStart, int yearEnd) {
	if (!sYear) {
		sYear = newSchoolYear(yearStart, yearEnd);
		return;
	}
	schoolYear* cur = sYear;
	while (cur && cur->next)
		cur = cur->next;
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
	int no;
	while (f >> no) {
		int ID;
		string FirstName, LastName;
		bool gender;
		date dateOfBirth;
		string idSocial;

		//get NO
		f.ignore(1000, ',');

		//get ID
		f >> ID;
		f.ignore(1000, ',');

		//get name
		getline(f, FirstName, ',');
		getline(f, LastName, ',');

		//get gender
		char c;
		f >> c;
		f.ignore(1000, ',');
		if (c == 'F' || c == 'f') gender = 1; // 1 = female, 0 = male
		else gender = 0;

		//get DoB
		string DOB;
		getline(f, DOB, ',');
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

void addClass(schoolYear*& sYear) {
	cin.clear();
	fflush(stdin);
	cout << "Please enter class's name: ";
	string Cname;
	getline(cin, Cname);

	cout << "Please enter the path of CSV file: ";
	string filepath;
	getline(cin, filepath);

	if (!sYear->Class) sYear->Class = newClass(filepath, Cname);
	else {
		Classes* Class = sYear->Class;
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
		if (tmp->student) deleteStudent(tmp->student);
		Class = Class->next;
		delete tmp;
	}
}

void deleteYear(schoolYear*& sYear) {
	while (sYear) {
		schoolYear* tmp = sYear;
		if (tmp->Class) deleteClass(tmp->Class);
		sYear = sYear->next;
		delete tmp;
	}
}