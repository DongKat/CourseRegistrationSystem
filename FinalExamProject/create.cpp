#include "create.h"

using namespace std;

bool createFolder(string path)
{
	//true if folder existed
	int tmp=mkdir(path.c_str());
	if (tmp) return true;
	else return false;
}

void removeFolder(string path)
{
	rmdir(path.c_str());
}

void removeFile(string path)
{
	remove(path.c_str());
}

bool checkDate(date Date1, date Date2)
{ 
	// true if date1 before or same as date 2
	if (Date1.year<Date2.year) return 1;
	if (Date1.year>Date2.year) return 0;

	if (Date1.month<Date2.month) return 1;
	if (Date1.month>Date2.month) return 0;
	
	if (Date1.day<Date2.day) return 1;
	if (Date1.day>Date2.day) return 0;

	return 1;
}

bool createFolderSchoolYear(string path){	//false if this is new year
	bool checkNewYear = createFolder(path);
	createFolder(path+"\\Classes");
	createFolder(path+"\\Semesters");
	createFolder(path+"\\Semesters\\Sem 1");
	createFolder(path+"\\Semesters\\Sem 2");
	createFolder(path+"\\Semesters\\Sem 3");
	return checkNewYear;
}

bool inputSchoolYear(){ 						//false if this is new SchoolYear
	int syear,eyear;
	do{
		cout << "Please input schoolyear: ";
		cin >> syear;
		eyear = syear + 1;

	} while (syear < 0);

	Schoolyear = to_string(syear)+"-"+to_string(eyear);
	return createFolderSchoolYear(Schoolyear);
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
	ofstream fout;
	fout.open(folder+"\\"+className+"\\"+className+".csv");
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
		fout << no << ","<< ID << "," << FirstName << "," << LastName << "," << gender << "," << DOB << "," << idSocial << "\n";
	}
	f.close();
	fout.close();
	return Class;
}

void createFolderClass(string path,string Cname){
	createFolder(path+"\\Classes\\"+Cname);
}

void addClass(Classes *&Class, string folder) {
	cin.clear();
	fflush(stdin);

	Classes *tmpClass=Class;

	while (tmpClass && tmpClass->next) tmpClass=tmpClass->next;

	string Cname;

	while (1){                       							// lay ten lop
		cout << "Please enter class's name: ";
		getline(cin, Cname);
		if (createFolder(folder+"\\Classes\\"+Cname)){
			cout <<"Error! This class has already existed!\n";
		}
		else break;
	}

	fstream f;

	f.open(folder+"\\Classes\\Classes.txt", ios::app | ios::out);   //ghi ten lop ra file
	f << Cname << "\n";
	f.close();

	string filepath;

	do{																//lay danh sach lop
		filepath.clear();
		cout << "Please enter the path of CSV file: ";
		getline(cin, filepath);

		f.open(filepath);

		if (!f.is_open()) cout << "Error! File is not found!\n";
	} while (!f.is_open());

	f.close();

	if (Class) tmpClass->next = newClass(filepath, Cname,folder+"\\Classes");
	else {
		Class=newClass(filepath,Cname,folder+"\\Classes");
	}
}

void deleteAllStudents(Students*& stu) {
	while (stu) {
		Students* tmp = stu;
		stu = stu->next;
		delete tmp;
	}
}

void deleteAllClasses(Classes*& Class) {
	while (Class) {
		Classes* tmp = Class;
		Class = Class->next;
		delete tmp;
	}
}

Semesters newSemester(int currSem, date begin, date end)
{	
	Semesters newSemester;
	newSemester.sem = currSem;
	newSemester.dateStart = begin;
	newSemester.dateEnd = end;

	return newSemester;
}

void addSemester(Semesters *semester, int currSem, date begin, date end)
{
	semester[currSem - 1] = newSemester(currSem, begin, end);
	Sem = "Sem " + to_string(currSem);
	createFolder(Schoolyear + "/Semesters/" + Sem);
}

void addNewSemesterMain(Semesters *semester)
{
	int currSem;
	date begin, end;

	cout << "You are creating new semester\n\n";
	cout << "Enter semester: ";
	cin >> currSem;

	cout << "Enter starting date:\n";
	cout << "Day: ";
	cin >> begin.day;
	cout << "Month: ";
	cin >> begin.month;
	cout << "Year: ";
	cin >>  begin.year;


	cout << "Enter ending date:\n";
	cout << "Day: ";
	cin >> end.day;
	cout << "Month: ";
	cin >> end.month;
	cout << "Year: ";
	cin >>  end.year;

	cin.ignore();

	addSemester(semester, currSem, begin, end);
}

Courses *newCourse(string courseName, string courseID, string teacherName, int numCredits, int maxStudent, Schedules schedule[])
{
	Courses *newCourse = new Courses;
	newCourse -> sem = Sem[4] - '0';
	newCourse -> courseName = courseName;
	newCourse -> courseID = courseID;
	newCourse -> teacherName = teacherName;
	newCourse -> numCredits = numCredits;
	newCourse -> maxStudent =  maxStudent;
	newCourse -> schedule[0] = schedule[0];
	newCourse -> schedule[1] = schedule[1];


	newCourse -> prev = NULL;
	newCourse -> next = NULL;

	return newCourse;
}

Courses *addCourse(Courses *&course, string courseName, string courseID, string teacherName, int numCredits, int maxStudent, Schedules *schedule)
{
	Courses *newC = newCourse(courseName, courseID, teacherName, numCredits, maxStudent, schedule);

	if (!course)
	{
		course = newC;
		return newC;
	}

	Courses *curr = course;
	while (curr -> next)
		curr = curr -> next;

	curr -> next = newC;
	curr -> next -> prev = curr;

	return newC;
}

void createFolderNFileCourse(Courses *course)
{
	ofstream out;

	createFolder(Schoolyear + "/Semesters/" + "/Sem "  + to_string(course -> sem) + '/' + course -> courseID);

	out.open(Schoolyear + "/Semesters/" + "/Sem " + to_string(course -> sem) + '/' + course -> courseID + "/Profile.csv");
	
	out << "Course ID,Course Name,Teacher Name,Num of Credits,Max Students,Session 1,Session 2\n";

	out << course -> courseID + ',' + course -> courseName + ',' + course -> teacherName + ',' + to_string(course -> numCredits) + ',' + to_string(course -> maxStudent) + ',' + course -> schedule[0].day + ' ' + course -> schedule[0].time + ',' + course -> schedule[1].day + ' '  +course -> schedule[1].time + '\n';

	out.close();

	out.open(Schoolyear + "/Semesters/" + "/Sem " + to_string(course -> sem) + '/' + course -> courseID + "/Scoreboard.csv");

	out << "No,Student ID,First Name,Last Name,Class,Midterm,Final,Bonus,Overall";

	out.close();
}

void viewCourseFile(Courses *course)
{
	ofstream out;

	Courses *curr = course;

	out.open(Schoolyear + "/Semesters/" + "/Sem "  + to_string(course -> sem) + "/AllCourses.csv");

	out << "Course ID,Course Name,Teacher Name";

	while (curr)
	{
		out << '\n' << curr -> courseID + ',' + curr -> courseName + ',' + curr -> teacherName;
		curr = curr -> next;
	}

	out.close();
}

Courses *findCourse(Courses *&course, string courseID, string courseName, string teacherName)
{
	Courses *curr = course;

	while (curr)
	{
		if (curr -> courseID == courseID && curr -> courseName == courseName && curr -> teacherName == course -> teacherName)
			return curr;
		curr = curr -> next;
	}

	return NULL;
}

void deleteCourse(Courses *&course, Courses *delCourse)
{
	ifstream in;

	string delPath = (Schoolyear + "/Semesters/" + "/Sem " + to_string(course->sem) + '/' + course->courseID);

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

void addNewCourseMain(Courses *&course)
{
	string courseID, courseName, teacherName;
	int numCredits, maxStudent;
	cout << "You are creating new course:\n\n";

	cout << "Enter course's ID: ";
	getline(cin, courseID);

	cout << "Enter course's name: ";
	getline(cin, courseName);

	cout << "Enter course's name of teacher: ";
	getline(cin, teacherName);

	cout << "Enter course's credits: ";
	cin >> numCredits;

	cout << "Enter course's max student: ";
	cin >> maxStudent;

	cin.ignore();

	Schedules schedule[2];

	for (int i = 0; i < 2; ++i)
	{
		cout << "Enter session:\n\n";
		cout << "Day of week: "; // MON, THU
		getline(cin, schedule[i].day);
		cout << "Time: ";		//S1, S2, S3
		getline(cin, schedule[i].time);
	}


	Courses *newCourse = addCourse(course, courseName, courseID, teacherName, numCredits, maxStudent, schedule);
	createFolderNFileCourse(newCourse);
	viewCourseFile(course);
}

void deleteCourseMain(Courses *&course, string courseID, string courseName, string teacherName)
{
	Courses *del = findCourse(course, courseID, courseName, teacherName);

	if (del)
		deleteCourse(course, del);
	else
		cout << "There are no course match with your information\n";
}

void editCourseMain(Courses *&course, string courseID, string courseName, string teacherName)
{
	Courses *edit = findCourse(course, courseID, courseName, teacherName);

	if (edit)
	{
		deleteCourse(course, edit); //error
		addNewCourseMain(course);
	}
	else
		cout << "There are no course match with your information\n";
}

bool loadCoursesFromFile(Courses *&course)
{

	ifstream in;

	string ignore;

	in.open(Schoolyear + "/Semesters/" + Sem + "/AllCourses.csv");

	if (!in.is_open())
		return false;
 
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
	Courses *curr = nullptr;

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

		BasicStudents *currStu = nullptr;
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
			getline(in, currStu -> className, ',');

			getline(in, ignore);
		}

		in.close();
	}
	
	return true;
}
