#include "create.h"

using namespace std;

void createFolder(string path){
	_mkdir(path.c_str());
}

void removeFolder(string path){
	_rmdir(path.c_str());
}

void removeFile(string path)
{
	_remove(path.c_str());
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

void createFolderSchoolYear(string path){
	createFolder(path);
	createFolder(path+"\\Classes");
	createFolder(path+"\\Semesters");
	createFolder(path+"\\Semesters\\Sem 1");
	createFolder(path+"\\Semesters\\Sem 2");
	createFolder(path+"\\Semesters\\Sem 3");
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
	createFolderSchoolYear(to_string(sYear->yearStart)+"-"+to_string(sYear->yearEnd));
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

void createFolderStudent(string path){
	createFolder(path);
	ofstream f;

	f.open(path+"\\Course Sem 1.csv");
	f.close();

	f.open(path+"\\Course Sem 2.csv");
	f.close();

	f.open(path+"\\Course Sem 3.csv");
	f.close();
	
	f.open(path+"\\Profile.txt");
	f.close();
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

	createFolderStudent(folder+"\\"+ID);

	ofstream f;
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
			stu->next = newStudent(no, ID, FirstName, LastName, gender, dateOfBirth, idSocial, className,folder+"\\"+className);
			stu->next->prev=stu;
			stu = stu->next;
		}
		else {
			Class->student = newStudent(no, ID, FirstName, LastName, gender, dateOfBirth, idSocial, className,folder+"\\"+className);
			stu = Class->student;
		}
	}
	f.close();
	return Class;
}

void createFolderClass(string path,string Cname){
	createFolder(path+"\\Classes\\"+Cname);
}

void addClass(schoolYear*& sYear, string folder) {
	cin.clear();
	fflush(stdin);
	cout << "Please enter class's name: ";
	string Cname;
	getline(cin, Cname);

	createFolderClass(folder, Cname);

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

	if (!sYear->Class) sYear->Class = newClass(filepath, Cname,folder+"\\Classes");
	else {
		Classes* Class = sYear->Class;
		while (Class->next) Class = Class->next;
		Class->next = newClass(filepath, Cname,folder+"\\Classes");
		Class->next->prev = Class;
	}
}

void deleteStudentFile(string path){
	string filepath=path+"\\Course Sem 1.csv";
	remove(filepath.c_str());

	filepath=path+ "\\Course Sem 2.csv";
	remove(filepath.c_str());

	filepath=path+ "\\Course Sem 3.csv";
	remove(filepath.c_str());

	filepath=path+ "\\Profile.txt";
	remove(filepath.c_str());

	removeFolder(path);
}

void deleteAllStudents(Students*& stu, string path) {
	while (stu) {
		Students* tmp = stu;
		stu = stu->next;
	
		deleteStudentFile(path+"\\"+tmp->ID);

		delete tmp;
	}
}

void deleteStudent(Students *&stu, string path){
	deleteStudentFile(path+"\\"+stu->ID);
	
	if (stu->next) stu->next->prev=stu->prev;
	if (stu->prev) stu->prev->next=stu->next;
	delete stu;
}

void deleteClassFolder(string path){
	removeFolder(path);
}

void deleteAllClasses(Classes*& Class, string path) {
	while (Class) {
		Classes* tmp = Class;
		if (tmp->student) deleteAllStudents(tmp->student,path+"\\" +Class->className);
		deleteClassFolder(path+"\\"+Class->className);
		Class = Class->next;
		delete tmp;
	}
}

void deleteSchoolYearFolder(string path){
	removeFolder(path+"\\Classes");
	removeFolder(path+"\\Semesters\\Sem 1");
	removeFolder(path+"\\Semesters\\Sem 2");
	removeFolder(path+"\\Semesters\\Sem 3");
	removeFolder(path+"\\Semesters");
	removeFolder(path);
}

void deleteAllYears(schoolYear*& sYear) {
	while (sYear) {
		schoolYear* tmp = sYear;
		if (tmp->Class) deleteAllClasses(tmp->Class,to_string(sYear->yearStart)+"-"+to_string(sYear->yearEnd)+"\\Classes");
		deleteSchoolYearFolder(to_string(sYear->yearStart)+"-"+to_string(sYear->yearEnd));
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
	deleteSchoolYearFolder(to_string(sYear->yearStart)+"-"+to_string(sYear->yearEnd));

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
	Sem = "Sem " + to_string(currSem);
}

Courses *newCourse(int currSem, date begin, date end, string courseName, string courseID, string teacher_name, int numCredits, int maxStudent, Schedules schedule[])
{
	Courses *newCourse = new Courses;
	newCourse -> sem = currSem;
	newCourse -> dateStart = begin;
	newCourse -> dateEnd = end;
	newCourse -> courseName = courseName;
	newCourse -> courseID = courseID;
	newCourse -> teacherName = teacher_name;
	newCourse -> numCredits = numCredits;
	newCourse -> maxStudent =  maxStudent;
	newCourse -> schedule[0] = schedule[0];
	newCourse -> schedule[1] = schedule[1];


	newCourse -> prev = NULL;
	newCourse -> next = NULL;

	return newCourse;
}


void addCourse(Courses *&course, int currSem, date begin, date end, string courseName, string courseID, string teacher_name, int numCredits, int maxStudent, Schedules *schedule)
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

void creatFolderNFileCourse(Courses *course)
{
	ofstream out;

	createFolder(Schoolyear + "/Semesters/" + "/Sem "  + to_string(course -> sem) + '/' + course -> courseID);

	out.open(Schoolyear + "/Semesters/" + "/Sem " + to_string(course -> sem) + '/' + course -> courseID + "/Profile.csv");
	
	out << "Course ID,Course Name,Teacher Name,Num of Credits,Max Students,Session 1,Session 2\n";
	out << course -> courseID + ',' + course -> courseName + ',' + course -> teacherName + ',' + "Credits: " + to_string(course -> numCredits) + "MaxStu: " + to_string(course -> maxStudent) + ',' + course -> schedule[0].day + ' ' course -> schedule[0].time + ',' + course -> schedule[1].day + ' ' course -> schedule[1].time + '\n';

	out.close();

	out.open(Schoolyear + "/Semesters/" + "/Sem " + to_string(course -> sem) + '/' + course -> courseID + "/Scoreboard.csv");

	out << "No,Student ID,First Name,Last Name,Midterm,Final,Bonus,Overall\n";

	out.close();
}


Courses *findCourse(Courses *&course, string courseID, string courseName, string teacher_name)
{
	Courses *curr = course;

	while (curr)
	{
		if (curr -> courseID == courseID && curr -> courseName == courseName && curr -> teacherName == course->teacherName)
			return curr;
		curr = curr -> next;
	}

	return NULL;
}

void deleteCourse(Courses *&course, Courses *delCourse)
{
	ifstream in;

	string delPath = (schoolyear + "/Semesters/" + "/Sem " + to_string(course -> sem) + '/' + course -> courseID)

	removeFile(delPath + "/Profile.csv");
	removeFile(delPath + "/Scoreboard.csv");
	removeFolder(delPath);

	if (delCourse -> prev)
		delCourse -> prev -> next = delCourse -> next;
	else
		course = delCourse -> next;

	if (delCourse -> next)
		delCourse -> next -> prev = delCourse -> prev;

	delete delCourse;
}

void deleteCourseMain(Courses *&course, string courseID, string courseName, string teacher_name)
{
	Courses *del = findCourse(course, courseID, courseName, teacher_name);

	if (del)
		deleteCourse(course, del);
	// else
	// cout ra la nguoi dung nhap sai cmnr
}


void viewCourseFile(Courses *course)
{
	ofstream out;

	Courses *curr = course;

	out.open(Schoolyear + "/Semesters/" + "/Sem "  + to_string(course -> sem) + "AllCourses");

	while (curr)
		out << curr -> courseID + ',' + curr -> courseName + ',' + curr -> teacherName + '\n';

	out.close();
}

void loadCoursesFromFile(Courses *&course)
{

	ifstream in;

	string ignore;

	in.open(Schoolyear + "/Semesters/" + Sem + "/AllCourses.csv");
 
	int count = 0;

	while (!in.eof())
	{
		++count;
		getline(in, ignore);
	}

	in.close();

	string *getCourse = new string[count];

	in.open(Schoolyear + "/Semesters/" + Sem + "/AllCourses.csv");

	count = -1;

	while (!in.eof())
	{
		getline(in, getCourse[++count], ',');
		getline(in, ignore);
	}

	in.close();
	Courses *curr;

	for (int i = 0; i <= count; ++i)
	{
		if (course == NULL)
		{
			course = new Courses;
			curr = course;
		}
		else
		{
			curr -> next = new Courses;
			curr = curr -> next;
		}


		in.open(Schoolyear + "/Semesters/" + Sem + '/' + getCourse[i] + "/Profile.csv");
		getline(in, ignore);

		curr -> sem = Sem[4] - '0';
		getline(in, curr -> courseID, ',');
		getline(in, curr -> courseName, ',');
		getline(in, curr -> teacherName,  ',');
		in >> curr -> numCredits;
		in.ignore();
		in >> curr -> maxStudent;
		in.ignore();
		getline(in, curr -> schedule[0].day, ' ');
		getline(in, curr -> schedule[0].time, ',');
		getline(in, curr -> schedule[1].day, ' ');
		getline(in, curr -> schedule[1].time);

		in.close();

		in.open(Schoolyear + "/Semesters/" + Sem + '/' + getCourse[i] + "/Scoreboard.csv");
		getline(in, ignore);

		BasicStudents *currStu;
		curr -> studentID = NULL;

		while (!in.eof())
		{
			if (curr -> studentID == NULL)
			{
				curr -> studentID = new BasicStudents;
				currStu = curr -> studentID;
			}
			else
			{
				currStu -> next = new BasicStudents;
				currStu = currStu -> next;
			}

			in >> currStu -> No;
			in.ignore();
			getline(in, currStu -> ID, ',');
			getline(in, currStu -> firstName, ',');
			getline(in, currStu -> lastName, ',');

			getline(in, ignore);
		}

		in.close();
	}
	

}
