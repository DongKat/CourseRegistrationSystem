#include "create.h"
#include "Library.h"
#include "Struct.h"

using namespace std;

void createFolder(string path){
	_mkdir(path.c_str());
}

void removeFolder(string path){
	_rmdir(path.c_str());
}

bool checkDate(date Date1, date Date2){  // true if date1 before or same as date 2
	if (Date1.year<Date2.year) return 1;
	if (Date1.year>Date2.year) return 0;

	if (Date1.month<Date2.month) return 1;
	if (Date1.month>Date2.month) return 0;
	
	if (Date1.day<Date2.day) return 1;
	if (Date1.day>Date2.day) return 0;

	return 1;
}

schoolYear* newSchoolYear(int yearStart, int yearEnd) {
	schoolYear* newYear = new schoolYear;
	newYear->yearStart = yearStart;
	newYear->yearEnd = yearEnd;
	newYear->Class = 0;
	newYear->next = 0;
	newYear->prev = 0;
	return newYear;
}

void addSchoolYear(schoolYear*& sYear, int yearStart, int yearEnd) {
	if (!sYear) {
		sYear = newSchoolYear(yearStart, yearEnd);
		
	}
	else{
		schoolYear* cur = sYear;
		while (cur && cur->next)
		cur = cur->next;
		cur->next = newSchoolYear(yearStart, yearEnd);
		cur->next->prev = cur;
	}
	createFolder(to_string(yearStart)+"-"+to_string(yearEnd));
	createFolder(to_string(yearStart)+"-"+to_string(yearEnd)+"\\Classes");
	createFolder(to_string(yearStart)+"-"+to_string(yearEnd)+"\\Semesters");
}

date convertToDay(string Day) {
	date ans = { 0,0,0 };
	int i=0;
	while (Day[i]!='/'){
		ans.day*=10;
		ans.day+=Day[i]-'0';
		++i;
	}
	++i;
	while (Day[i]!='/'){
		ans.month*=10;
		ans.month+=Day[i]-'0';
		++i;
	}
	++i;
	while (i<Day.length()){
		ans.year*=10;
		ans.year+=Day[i]-'0';
		++i;
	}
	return ans;
}

void printDateToFile(date Date, ofstream &f){
	if (Date.day<10) f << 0;
	f << Date.day << "/";
	if (Date.month<10) f <<0;
	f << Date.month << "/" << Date.year;
}

void printDateToConsole(date Date){
	if (Date.day<10) cout << 0;
	cout << Date.day << "/";
	if (Date.month<10) cout <<0;
	cout << Date.month << "/" << Date.year;
}

Students* newStudent(int no, string ID, string FirstName, string LastName, string gender, date dateOfBirth, string idSocial, string className, string folder) {
	Students* stu = new Students;
	stu->no = no;
	stu->ID = ID;
	stu->firstName = FirstName;
	stu->lastName = LastName;
	stu->gender = gender;
	stu->dateOfBirth = dateOfBirth;
	stu->idSocial = idSocial;
	stu->className=className;
	stu->next = nullptr;
	stu->prev=nullptr;

	createFolder(folder+"\\"+ID);

	ofstream f;
	f.open(folder+"\\"+ID+"\\Course Sem 1.csv");
	f.close();
	f.open(folder+"\\"+ID+"\\Course Sem 2.csv");
	f.close();
	f.open(folder+"\\"+ID+"\\Course Sem 3.csv");
	f.close();
	f.open(folder+"\\"+ID+"\\Profile.txt");
		f << no << "\n" << ID << "\n" << FirstName << "\n" << LastName << "\n" << gender << "\n";
		printDateToFile(dateOfBirth,f);
		f << "\n" << idSocial;
	f.close();

	return stu;
}

Classes* newClass(string filepath, string className, string folder) {
	Classes* Class = new Classes;
	Class->next = nullptr;
	Class->student = nullptr;
	Class->className = className;
	ifstream f;
	f.open(filepath);
	Students* stu = nullptr;
	int no;
	while (f >> no) {
		string ID;
		string FirstName, LastName;
		string gender;
		date dateOfBirth;
		string idSocial;

		//get NO
		f.ignore(1000, ',');

		//get ID
		getline(f,ID,',');

		//get name
		getline(f, FirstName, ',');
		getline(f, LastName, ',');

		//get gender
		getline(f,gender,',');

		//get DoB
		string DOB;
		getline(f, DOB, ',');
		dateOfBirth = convertToDay(DOB);

		//get social ID
		getline(f, idSocial);

		//add to class
		if (Class->student) {
			stu->next = newStudent(no, ID, FirstName, LastName, gender, dateOfBirth, idSocial, className,folder);
			stu->next->prev=stu;
			stu = stu->next;
		}
		else {
			Class->student = newStudent(no, ID, FirstName, LastName, gender, dateOfBirth, idSocial, className,folder);
			stu = Class->student;
		}
	}
	f.close();
	return Class;
}

void addClass(schoolYear*& sYear, string folder) {
	cin.clear();
	fflush(stdin);
	cout << "Please enter class's name: ";
	string Cname;
	getline(cin, Cname);

	folder+="\\Classes\\"+Cname;

	createFolder(folder.c_str());

	fstream f;
	string filepath;

	do{
		filepath.clear();
		cout << "Please enter the path of CSV file: ";
		getline(cin, filepath);

		f.open(filepath);

		if (!f.is_open()) cout << "Error! File is not found!\n";
	} while (!f.is_open());

	f.close();

	if (!sYear->Class) sYear->Class = newClass(filepath, Cname,folder);
	else {
		Classes* Class = sYear->Class;
		while (Class->next) Class = Class->next;
		Class->next = newClass(filepath, Cname,folder);
		Class->next->prev = Class;
	}
}

void deleteAllStudents(Students*& stu, string path) {
	while (stu) {
		Students* tmp = stu;
		stu = stu->next;

		string filepath=path+"\\"+tmp->ID+"\\Course Sem 1.csv";
		remove(filepath.c_str());

		filepath=path+"\\"+tmp->ID+"\\Course Sem 2.csv";
		remove(filepath.c_str());

		filepath=path+"\\"+tmp->ID+"\\Course Sem 3.csv";
		remove(filepath.c_str());

		filepath=path+"\\"+tmp->ID+"\\Profile.txt";
		remove(filepath.c_str());

		removeFolder(path+"\\" + tmp->ID);
		delete tmp;
	}
}

void deleteStudent(Students *&stu, string path){
	removeFolder(path+"\\"+stu->ID);
	if (stu->next) stu->next->prev=stu->prev;
	if (stu->prev) stu->prev->next=stu->next;
	delete stu;
}

void deleteAllClasses(Classes*& Class, string path) {
	while (Class) {
		Classes* tmp = Class;
		if (tmp->student) deleteAllStudents(tmp->student,path+"\\" +Class->className);
		Class = Class->next;
		removeFolder(path+"\\"+tmp->className);
		delete tmp;
	}
}

void deleteAllYears(schoolYear*& sYear) {
	while (sYear) {
		schoolYear* tmp = sYear;
		if (tmp->Class) deleteAllClasses(tmp->Class,to_string(sYear->yearStart)+"-"+to_string(sYear->yearEnd)+"\\Classes");
		removeFolder(to_string(sYear->yearStart)+"-"+to_string(sYear->yearEnd));
		sYear = sYear->next;
		delete tmp;
	}
}

void deleteClass(Classes *&Class, string path){
	removeFolder(path+"\\"+Class->className);
	if (Class->student) deleteAllStudents(Class->student,path+Class->className);
	if (Class->next) Class->next->prev=Class->prev;
	if (Class->prev) Class->prev->next=Class->next;
}

void deleteYear(schoolYear *&sYear){
	removeFolder(to_string(sYear->yearStart)+"-"+to_string(sYear->yearEnd));
	if (sYear->Class) deleteAllClasses(sYear->Class,to_string(sYear->yearStart)+"-"+to_string(sYear->yearEnd)+"\\Classes");
	if (sYear->next) sYear->next->prev=sYear->prev;
	if (sYear->prev) sYear->prev->next=sYear->next;
}

Semesters newSemester(int currSem, date begin, date end)
{	
	Semesters newSemester;
	newSemester.sem = currSem;
	newSemester.dateStart = begin;
	newSemester.dateEnd = end;

	return newSemester;
}

void addSemester(Semesters semester[], int currSem, date begin, date end)
{
	semester[currSem - 1] = newSemester(currSem, begin, end);
}

Courses *newCourse(int currSem, date begin, date end, string courseName, string courseID, string teacher_name, int numCredits, int maxStudent, Schedules schedule[])
{
	Courses *newCourse = new Courses;
	newCourse -> sem = currSem;
	newCourse -> dateStart = begin;
	newCourse -> dateEnd = end;
	newCourse -> courseName = courseName;
	newCourse -> courseID = courseID;
	newCourse -> teacher_name = teacher_name;
	newCourse -> numCredits = numCredits;
	newCourse -> maxStudent =  maxStudent;
	newCourse -> schedule[0] = schedule[0];
	newCourse -> schedule[1] = schedule[1];


	newCourse -> prev = NULL;
	newCourse -> next = NULL;

	return newCourse;
}


void addCourse(Courses *&course, int currSem, date begin, date end, string courseName, string courseID, string teacher_name, int numCredits, int maxStudent, Schedules *&schedule)
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

void extractCourse(Courses *course)
{
	ofstream out;

	createFolder(schoolyear + "/Semesters/" + "/Sem "  + to_string(course -> sem) + '/' + course -> courseID);

	out.open(schoolyear + "/Semesters/" + "/Sem " + to_string(course -> sem) + '/' + course -> courseID + "/Profile.csv");
	
	out << course -> courseID + ',' + course -> courseName + ',' + course -> teacher_name + ',' + "Credits: " + to_string(course -> numCredits) + "MaxStu: " + to_string(course -> maxStudent);

	out.close();

	out.open(schoolyear + "/Semesters/" + "/Sem " + to_string(course -> sem) + '/' + course -> courseID + "/Scoreboard.csv");

	out << "No,Student ID,First Name,Last Name,Midterm,Final,Bonus,Overall";

	out.close();
}

void deleteCourse(Courses *&course, Courses *delCourse) // delete 1 course thoi
{
	if (delCourse -> prev)
		delCourse -> prev -> next = delCourse -> next;
	else
		course = delCourse -> next;

	if (delCourse -> next)
		delCourse -> next -> prev = delCourse -> prev;

	delete delCourse;
}