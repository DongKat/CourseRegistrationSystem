#include "create.h"

using namespace std;

bool createFolder(string path) //true if folder existed
{
	int tmp = mkdir(path.c_str());
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

bool checkDate(date Date1, date Date2) {  // true if date1 before or same as date 2
	if (Date1.year < Date2.year) return 1;
	if (Date1.year > Date2.year) return 0;

	if (Date1.month < Date2.month) return 1;
	if (Date1.month > Date2.month) return 0;

	if (Date1.day < Date2.day) return 1;
	if (Date1.day > Date2.day) return 0;

	return 1;
}

bool createFolderSchoolYear(string path) {	//false if this is new year
	bool checkNewYear = createFolder(path);
	createFolder(path + "\\Classes");

	//Duy da o day
	createFolder(path + "/Semesters");
	ofstream out;
	out.open("YearAndSemester.txt");
	out << Schoolyear + '\n';
	out.close();
	// Chao duy Anh cung comment o day

	return checkNewYear;
}

bool inputSchoolYear() { 						//false if this is new SchoolYear
	int syear, eyear;
	int temp = 20;
	txtColor(15);
	do {
		gotoxy(70, temp);
		cout << "Please intput start year: ";
		cin >> syear;
		temp++;
		eyear = syear + 1;
	} while (syear < 0);

	Schoolyear = to_string(syear) + "-" + to_string(eyear);
	return createFolderSchoolYear(Schoolyear);
}

date convertToDay(string Day)
{
	date ans = { 0,0,0 };
	/*
	stringstream s(Day);
	string temp;
	getline(s, temp, '/');
	ans.day = stoi(temp);
	getline(s, temp, '/');
	ans.month = stoi(temp);
	getline(s, temp, '/');
	ans.year = stoi(temp);
	- DCat -
	*/
	int i = 0;
	while (Day[i] != '/') {
		ans.day *= 10;
		ans.day += Day[i] - '0';
		++i;
	}
	++i;
	while (Day[i] != '/') {
		ans.month *= 10;
		ans.month += Day[i] - '0';
		++i;
	}
	++i;
	while (i < Day.length()) {
		ans.year *= 10;
		ans.year += Day[i] - '0';
		++i;
	}
	return ans;
}

void printDateToFile(date Date, ofstream& f) {
	if (Date.day < 10) f << 0;
	f << Date.day << "/";
	if (Date.month < 10) f << 0;
	f << Date.month << "/" << Date.year;
}

void printDateToConsole(date Date) {
	if (Date.day < 10) cout << 0;
	cout << Date.day << "/";
	if (Date.month < 10) cout << 0;
	cout << Date.month << "/" << Date.year;
}

void createFolderStudent(string path) {
	createFolder(path);
	ofstream f;

	f.open(path + "\\Course Sem 1.csv");
	f.close();

	f.open(path + "\\Course Scoreboard Sem 1.csv");
	f.close();

	f.open(path + "\\Course Sem 2.csv");
	f.close();

	f.open(path + "\\Course Scoreboard Sem 2.csv");
	f.close();

	f.open(path + "\\Course Sem 3.csv");
	f.close();

	f.open(path + "\\Course Scoreboard Sem 3.csv");
	f.close();

	f.open(path + "\\Profile.txt");
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
	stu->className = className;
	stu->next = nullptr;
	stu->prev = nullptr;

	createFolderStudent(folder + "\\" + ID);

	ofstream f;
	f.open(folder + "\\" + ID + "\\Profile.txt");
	f << no << "\n" << ID << "\n" << FirstName << "\n" << LastName << "\n" << gender << "\n";
	printDateToFile(dateOfBirth, f);
	f << "\n" << idSocial << endl << className;
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
	fout.open(folder + "\\" + className + "\\allStudents.txt");
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
		getline(f, ID, ',');

		//get name
		getline(f, FirstName, ',');
		getline(f, LastName, ',');

		//get gender
		getline(f, gender, ',');

		//get DoB
		string DOB;
		getline(f, DOB, ',');
		dateOfBirth = convertToDay(DOB);

		//get social ID
		getline(f, idSocial);

		//add to class
		if (Class->student) {
			stu->next = newStudent(no, ID, FirstName, LastName, gender, dateOfBirth, idSocial, className, folder + "\\" + className);
			stu->next->prev = stu;
			stu = stu->next;
		}
		else {
			Class->student = newStudent(no, ID, FirstName, LastName, gender, dateOfBirth, idSocial, className, folder + "\\" + className);
			stu = Class->student;
		}
		fout << ID << "\n";
	}
	f.close();
	fout.close();
	return Class;
}

void createFolderClass(string path, string Cname) {
	createFolder(path + "\\Classes\\" + Cname);
}

void addClass(Classes*& Class, string folder) {
	txtColor(15);
	if (Schoolyear == "") {
		gotoxy(70, 20);
		cout << "You must create school year first!\n";
		Sleep(1000);
		return;
	}

	Classes* tmpClass = Class;

	while (tmpClass && tmpClass->next) tmpClass = tmpClass->next;

	string Cname;

	int temp = 20;
	gotoxy(70, temp);
	cout << "Please enter class's name(Ex:20apcs1): ";
	getline(cin, Cname);

	while (createFolder(folder + "\\Classes\\" + Cname)) {   	// lay ten lop
		gotoxy(70, temp);
		cout << "Please enter class's name(Ex:20apcs1): ";
		getline(cin, Cname);
		temp++;
	}

	fstream f;

	f.open(folder + "\\Classes\\allClasses.txt", ios::app | ios::out);   //ghi ten lop ra file
	f << Cname << "\n";
	f.close();

	string filepath;

	gotoxy(17, 18); cout << "C S V   F I L E S";
	gotoxy(20, 19); cout << "17apcs1.csv";
	gotoxy(20, 20); cout << "17apcs2.csv";
	gotoxy(20, 21); cout << "18apcs1.csv";
	gotoxy(20, 22); cout << "18apcs2.csv";
	gotoxy(20, 23); cout << "19apcs1.csv";
	gotoxy(20, 24); cout << "19apcs2.csv";
	gotoxy(20, 25); cout << "20apcs1.csv";
	gotoxy(20, 26); cout << "20apcs2.csv";

	do {								//lay danh sach lop
		gotoxy(70, temp);
		filepath.clear();

		cout << "Please enter the path of CSV file: ";
		getline(cin, filepath);
		temp++;
		f.open(filepath);
	} while (!f.is_open());

	f.close();

	if (Class) tmpClass->next = newClass(filepath, Cname, folder + "\\Classes");
	else {
		Class = newClass(filepath, Cname, folder + "\\Classes");
	}

	autoGenerateStudentAccounts(filepath);
	autoGenerateStudentProfiles(filepath);
}

Semesters newSemester(int currSem, date begin, date end)
{
	Semesters newSemester;
	newSemester.sem = currSem;
	dateStart = begin;
	dateEnd = end;

	return newSemester;
}

bool loadYearAndSem()
{
	ifstream in;

	in.open("YearAndSemester.txt");

	if (!in.is_open())
		throw std::runtime_error("YearAndSemester.txt not found!");

	getline(in, Schoolyear);
	getline(in, Sem);

	in.close();
}

void addSemester(Semesters* semester, int currSem, date begin, date end)
{
	semester[currSem - 1] = newSemester(currSem, begin, end);
	Sem = "Sem " + to_string(currSem);
	createFolder(Schoolyear + "/Semesters/" + Sem);

	ofstream out;

	out.open("YearAndSemester.txt");
	out << Schoolyear + '\n' + Sem + '\n';
	out.close();
}

void addNewSemesterMain(Semesters* semester)
{
	if (Schoolyear == "") {
		gotoxy(70, 20);
		cout << "You must create school year first!\n";
		Sleep(1000);
		return;
	}

	txtColor(15);
	int currSem;
	date begin, end;

	gotoxy(67, 20);
	cout << "You are creating new semester\n\n";

	int temp = 21;

	do {
		gotoxy(70, temp);
		cout << "Enter semester(Ex:1): ";
		cin >> currSem;
		temp++;
	} while (currSem != 1 && currSem != 2 && currSem != 3);

	gotoxy(67, temp);
	cout << "Enter starting date:\n";
	temp++;

	do {
		gotoxy(70, temp);
		cout << "Day: ";
		cin >> begin.day;
		temp++;
		gotoxy(70, temp);
		cout << "Month: ";
		cin >> begin.month;
		temp++;
		gotoxy(70, temp);
		cout << "Year(In the range of School Year): ";
		cin >> begin.year;
		temp++;
	} while (!isLegalDate(begin));

	gotoxy(67, temp);
	cout << "Enter ending date:\n";
	temp++;

	do {
		gotoxy(70, temp);
		cout << "Day: ";
		cin >> end.day;
		temp++;
		gotoxy(70, temp);
		cout << "Month: ";
		cin >> end.month;
		temp++;
		gotoxy(70, temp);
		cout << "Year(In the range of School Year): ";
		cin >> end.year;
		temp++;
	} while (!isLegalDate(end));

	cin.ignore();

	addSemester(semester, currSem, begin, end);
}

Courses* newCourse(string courseName, string courseID, string teacherName, int numCredits, int maxStudent, Schedules schedule[])
{
	Courses* newCourse = new Courses;
	newCourse->sem = Sem[4] - '0';
	newCourse->courseName = courseName;
	newCourse->courseID = courseID;
	newCourse->teacherName = teacherName;
	newCourse->numCredits = numCredits;
	newCourse->maxStudent = maxStudent;
	newCourse->schedule[0] = schedule[0];
	newCourse->schedule[1] = schedule[1];

	newCourse->prev = NULL;
	newCourse->next = NULL;

	return newCourse;
}

Courses* addCourse(Courses*& course, string courseName, string courseID, string teacherName, int numCredits, int maxStudent, Schedules* schedule)
{
	Courses* newC = newCourse(courseName, courseID, teacherName, numCredits, maxStudent, schedule);

	if (!course)
	{
		course = newC;
		return newC;
	}

	Courses* curr = course;
	while (curr->next)
		curr = curr->next;

	curr->next = newC;
	curr->next->prev = curr;

	return newC;
}

void createFolderNFileCourse(Courses* course)
{
	ofstream out;

	createFolder(Schoolyear + "/Semesters/" + Sem + '/' + course->courseID);

	out.open(Schoolyear + "/Semesters/" + Sem + '/' + course->courseID + "/Profile.csv");

	out << "Course ID,Course Name,Teacher Name,Num of Credits,Max Students,Session 1,Session 2\n";

	out << course->courseID + ',' + course->courseName + ',' + course->teacherName + ',' + to_string(course->numCredits) + ',' + to_string(course->maxStudent) + ',' + course->schedule[0].day + ' ' + course->schedule[0].time + ',' + course->schedule[1].day + ' ' + course->schedule[1].time + '\n';

	out.close();

	out.open(Schoolyear + "/Semesters/" + Sem + '/' + course->courseID + "/Scoreboard.csv");

	out << "No,Student ID,First Name,Last Name,Class,Midterm,Final,Bonus,Overall";

	out.close();
}

void viewCourseFile(Courses* course)
{
	ofstream out;

	Courses* curr = course;

	out.open(Schoolyear + "/Semesters/" + Sem + "/AllCourses.csv");

	out << "Course ID,Course Name,Teacher Name";

	while (curr != NULL)
	{
		out << '\n' << curr->courseID + ',' + curr->courseName + ',' + curr->teacherName;
		curr = curr->next;
	}

	out.close();
}

Courses* findCourse(Courses*& course, string courseID, string courseName, string teacherName)
{
	Courses* curr = course;

	while (curr)
	{
		if (curr->courseID == courseID && curr->courseName == courseName && curr->teacherName == course->teacherName)
			return curr;
		curr = curr->next;
	}

	return NULL;
}

void deleteCourse(Courses*& course, Courses* delCourse)
{
	string delPath = (Schoolyear + "/Semesters/" + Sem + '/' + delCourse->courseID);

	removeFile(delPath + "/Profile.csv"); 		//xoa file profile
	removeFile(delPath + "/Scoreboard.csv");	//xoa file scorse
	removeFolder(delPath);

	if (delCourse->prev)
		delCourse->prev->next = delCourse->next;
	else
		course = delCourse->next;

	if (delCourse->next)
		delCourse->next->prev = delCourse->prev;

	delete delCourse;

	viewCourseFile(course);		//cap nhat lai linked list
}

void addNewCourseMain(Courses*& course)
{
	if (Sem == "") {
		gotoxy(70, 20);
		cout << "You must create semester first!\n";
		Sleep(1000);
		return;
	}
	txtColor(15);
	string courseID, courseName, teacherName;
	int numCredits, maxStudent;
	gotoxy(67, 20);
	cout << "You are creating new course:\n\n";

	int temp = 21;
	gotoxy(70, temp);
	cout << "Enter course's ID: ";
	getline(cin, courseID);
	temp++;

	gotoxy(70, temp);
	cout << "Enter course's name: ";
	getline(cin, courseName);
	temp++;

	gotoxy(70, temp);
	cout << "Enter course's name of teacher: ";
	getline(cin, teacherName);
	temp++;

	gotoxy(70, temp);
	cout << "Enter course's credits: ";
	cin >> numCredits;
	temp++;

	gotoxy(70, temp);
	cout << "Enter course's max student: ";
	cin >> maxStudent;
	temp++;

	cin.ignore();

	Schedules schedule[2];

	for (int i = 0; i < 2; ++i)
	{
		gotoxy(70, temp);
		cout << "Enter session:\n\n";
		temp++;
		gotoxy(70, temp);
		cout << "Day of week(From MON to SUN): "; // MON, THU
		getline(cin, schedule[i].day);
		temp++;
		gotoxy(70, temp);
		cout << "Time(S1, S2, S3): ";		//S1, S2, S3
		getline(cin, schedule[i].time);
		temp++;
	}

	Courses* newCourse = addCourse(course, courseName, courseID, teacherName, numCredits, maxStudent, schedule);
	createFolderNFileCourse(newCourse);
	viewCourseFile(course);
}

void deleteCourseMain(Courses*& course)
{
	string courseID, courseName, teacherName;

	cout << "You are deleting course:\n\n";

	cout << "Enter course's ID: "; //lay course id
	getline(cin, courseID);

	cout << "Enter course's name: ";	//lay course name
	getline(cin, courseName);

	cout << "Enter course's name of teacher: ";		//lay course teacher
	getline(cin, teacherName);

	Courses* del = findCourse(course, courseID, courseName, teacherName);

	if (del)
		deleteCourse(course, del);	//xoa course
	else
		cout << "There are no course match with your information\n";
}

void deleteCourseFolder(Courses* delCourse)
{
	string delPath = (Schoolyear + "/Semesters/" + Sem + '/' + delCourse->courseID);

	removeFile(delPath + "/Profile.csv");
	removeFile(delPath + "/Scoreboard.csv");
	removeFolder(delPath);
}

void editCourseMain(Courses*& course)
{
	txtColor(15);
	string courseID, courseName, teacherName;

	int temp = 20;
	gotoxy(70, temp);
	cout << "You are editting course:\n\n";
	temp++;

	gotoxy(70, temp);
	cout << "Enter course's ID: ";
	getline(cin, courseID);
	temp++;

	gotoxy(70, temp);
	cout << "Enter course's name: ";
	getline(cin, courseName);
	temp++;

	gotoxy(70, temp);
	cout << "Enter course's name of teacher: ";
	getline(cin, teacherName);
	temp++;

	//tim course de edit theo yeu cau cua staff
	Courses* edit = findCourse(course, courseID, courseName, teacherName);

	if (edit)
	{
		deleteCourseFolder(edit); 		//delete folder
		gotoxy(70, temp);
		cout << "You are editting course:\n\n";
		temp++;

		gotoxy(70, temp);
		cout << "Enter course's ID: ";
		getline(cin, edit->courseID);			//lay id moi
		temp++;

		gotoxy(70, temp);
		cout << "Enter course's name: ";
		getline(cin, edit->courseName);		//lay name moi
		temp++;

		gotoxy(70, temp);
		cout << "Enter course's name of teacher: ";
		getline(cin, edit->teacherName);		//lay teacher moi
		temp++;

		gotoxy(70, temp);
		cout << "Enter course's credits: ";
		cin >> edit->numCredits;				//lay tin chi moi
		temp++;

		gotoxy(70, temp);
		cout << "Enter course's max student: ";
		cin >> edit->maxStudent;				//lay max student moi
		temp++;

		cin.ignore();

		for (int i = 0; i < 2; ++i)
		{
			gotoxy(70, temp);
			cout << "Enter session\n";
			temp++;

			gotoxy(70, temp);
			cout << "Day of week(From MON to SUN): "; // MON, THU
			getline(cin, edit->schedule[i].day);		//lay thu day
			temp++;

			gotoxy(70, temp);
			cout << "Time(S1, S2, S3): ";		//S1, S2, S3
			getline(cin, edit->schedule[i].time);		//lay buoi moi
			temp++;
		}

		createFolderNFileCourse(edit);					//tao folder moi
		viewCourseFile(course);							//cap nhat lai file all courses
	}
	else {
		gotoxy(70, temp);
		cout << "There are no course match with your information\n";
		temp++;
		Sleep(1000);
	}
}

bool loadCoursesFromFile(Courses*& course)
{
	ifstream in;

	string ignore;

	in.open(Schoolyear + "/Semesters/" + Sem + "/AllCourses.csv");

	if (!in.is_open())
		throw std::runtime_error("Can't load Course from file");

	//Dem so luong courses de khai dynamic string
	int count = -1;

	while (!in.eof())
	{
		++count;
		getline(in, ignore);
	}

	in.close();

	string* getCourse = new string[count];

	in.open(Schoolyear + "/Semesters/" + Sem + "/AllCourses.csv");

	getline(in, ignore);

	//Lay ten courses vao strings
	count = -1;

	while (!in.eof())
	{
		getline(in, getCourse[++count], ',');
		getline(in, ignore);
	}

	in.close();

	Courses* curr = nullptr;

	//Truy cap vao folder bang string moi lay de lay thong tin chi tien cua course
	for (int i = 0; i <= count; ++i)
	{
		if (course == NULL)
		{
			course = new Courses;
			course->prev = course->next = NULL;
			curr = course;
		}
		else
		{
			curr->next = new Courses;
			curr->next->prev = curr;
			curr->next->next = NULL;
			curr = curr->next;
		}

		//mo file profile de lay thong tin cua course
		in.open(Schoolyear + "/Semesters/" + Sem + '/' + getCourse[i] + "/Profile.csv");
		getline(in, ignore);

		curr->sem = Sem[4] - '0';					//lay semester
		getline(in, curr->courseID, ',');			//lay course ID
		getline(in, curr->courseName, ',');		//lay course name
		getline(in, curr->teacherName, ',');		//lay teach name
		in >> curr->numCredits;					//lay numCredits
		in.ignore();
		in >> curr->maxStudent;					//lay max student
		in.ignore();
		getline(in, curr->schedule[0].day, ' ');	//bat dau lay shedule
		getline(in, curr->schedule[0].time, ',');
		getline(in, curr->schedule[1].day, ' ');
		getline(in, curr->schedule[1].time);

		in.close();

		//mo file scoreboard de lay thong tin hoc sinh
		in.open(Schoolyear + "/Semesters/" + Sem + '/' + getCourse[i] + "/Scoreboard.csv");

		//Dem so luong hoc sinh hien tai
		int countStu = -1;
		while (!in.eof())
		{
			++countStu;
			getline(in, ignore);
		}

		in.close();

		//neu co hoc sinh thi bat dau lay
		if (countStu > 0)
		{
			in.open(Schoolyear + "/Semesters/" + Sem + '/' + getCourse[i] + "/Scoreboard.csv");
			getline(in, ignore);

			BasicStudents* currStu = nullptr;

			//bat dau lay
			while (!in.eof())
			{
				if (curr->studentID == NULL)
				{
					curr->studentID = new BasicStudents;
					curr->studentID->prev = curr->studentID->next = NULL;
					currStu = curr->studentID;
				}
				else
				{
					currStu->next = new BasicStudents;
					currStu->next->prev = currStu;
					currStu->next->next = NULL;
					currStu = currStu->next;
				}

				in >> currStu->No;
				in.ignore();
				getline(in, currStu->ID, ',');			//lay id hoc sinh
				getline(in, currStu->firstName, ',');		//lay first name hoc sinh
				getline(in, currStu->lastName, ',');		//lay last name hoc sinh
				getline(in, currStu->className, ',');		//lay ten lop hoc sinh

				getline(in, ignore);
			}

			in.close();
		}
	}

	return (count != -1);
}

void viewCourse(Courses* course)
{
	cout << "Course's ID: " << course->courseID
		<< "\nCourse's Name: " << course->courseName
		<< "\nCourse's Teacher: " << course->teacherName
		<< "\nCourse's num of credits: " << course->numCredits
		<< "\nCourse's max student: " << course->maxStudent
		<< "\nCourse's first session: " << course->schedule[0].day << ' ' << course->schedule[0].time
		<< "\nCourse's second session: " << course->schedule[1].day << ' ' << course->schedule[1].time;
}

void viewCourseMain(Courses* course)
{
}