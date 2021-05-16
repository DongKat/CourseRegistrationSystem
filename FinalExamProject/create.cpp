#include "create.h"

// Auxiliary functions
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
bool checkDate(date Date1, date Date2) {  // true if date1 before or same as date 2
	if (Date1.year < Date2.year) return 1;
	if (Date1.year > Date2.year) return 0;

	if (Date1.month < Date2.month) return 1;
	if (Date1.month > Date2.month) return 0;

	if (Date1.day < Date2.day) return 1;
	if (Date1.day > Date2.day) return 0;

	return 1;
}
Courses* findCourse(Courses*& course, string courseID, string courseName, string teacherName)
{
	Courses* curr = course;

	while (curr)
	{
		if (curr->courseID == courseID && curr->courseName == courseName && curr->teacherName == teacherName)
			return curr;
		curr = curr->next;
	}

	return nullptr;
}

// Important funcitons, run at the start
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
		if (course == nullptr)
		{
			course = new Courses;
			course->prev = course->next = nullptr;
			curr = course;
		}
		else
		{
			curr->next = new Courses;
			curr->next->prev = curr;
			curr->next->next = nullptr;
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
		getline(in, curr->schedule[0].day, ',');	//bat dau lay shedule
		getline(in, curr->schedule[0].time, ',');
		getline(in, curr->schedule[1].day, ',');
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
		curr->countStudent = --countStu;

		in.close();

		//neu co hoc sinh thi bat dau lay
		if (countStu > 0)
		{
			in.open(Schoolyear + "/Semesters/" + Sem + '/' + getCourse[i] + "/Scoreboard.csv");
			getline(in, ignore);

			BasicStudents* currStu = nullptr;

			//bat dau lay
			while (in.peek() != EOF)
			{
				if (curr->studentID == nullptr)
				{
					curr->studentID = new BasicStudents;
					curr->studentID->prev = curr->studentID->next = nullptr;
					currStu = curr->studentID;
				}
				else
				{
					currStu->next = new BasicStudents;
					currStu->next->prev = currStu;
					currStu->next->next = nullptr;
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
bool loadYearAndSem()
{
	ifstream in;

	in.open("YearAndSemester.txt");

	if (!in.is_open())
	{
		ofstream out("YearAndSemester.txt");
		return false;
	}


	getline(in, Schoolyear);
	getline(in, Sem);
	in >> dateStart.day >> dateStart.month >> dateStart.year >> dateEnd.day >> dateEnd.month >> dateEnd.year;

	in.close();
	return true;
}
void viewCourseFile(Courses* course) // update course list ra file theo thoi gian thuc
{
	ofstream out;

	Courses* curr = course;

	out.open(Schoolyear + "/Semesters/" + Sem + "/AllCourses.csv");

	out << "Course ID,Course Name,Teacher Name";

	while (curr != nullptr)
	{
		out << '\n' << curr->courseID + ',' + curr->courseName + ',' + curr->teacherName;
		curr = curr->next;
	}

	out.close();
}


// Folder and file handling
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

	f.open(path + "\\Course Sem 1 Scoreboard.csv");
	f.close();

	f.open(path + "\\Course Sem 2.csv");
	f.close();

	f.open(path + "\\Course Sem 2 Scoreboard .csv");
	f.close();

	f.open(path + "\\Course Sem 3.csv");
	f.close();

	f.open(path + "\\Course Sem 3 Scoreboard.csv");
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

// For Create Schoolyear
bool inputSchoolYear() { 						//false if this is new SchoolYear
	int syear, eyear;
	int temp = 21;
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
bool createFolderSchoolYear(string path)
{
	//false if this is new year
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



// For create Class mewyu
Classes* newClass(string filepath, string className, string folder) {
	Classes* Class = new Classes;
	Class->next = nullptr;
	Class->student = nullptr;
	Class->className = className;
	ifstream f;
	ofstream fout;
	fout.open(folder + "\\" + className + "\\allStudents.csv");
	f.open(filepath);
	Students* stu = nullptr;
	string t;
	getline(f, t); // ignore field names
	while (f.peek() != EOF) {
		int no;
		string ID;
		string FirstName, LastName;
		string gender;
		date dateOfBirth;
		string idSocial;

		//get No
		getline(f, t, ',');
		no = stoi(t);

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
void addClass(Classes*& Class, string folder)
{
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

	gotoxy(17, 18); cout << "C S V   F I L E S";
	gotoxy(20, 19); cout << "17apcs1.csv";
	gotoxy(20, 20); cout << "17apcs2.csv";
	gotoxy(20, 21); cout << "18apcs1.csv";
	gotoxy(20, 22); cout << "18apcs2.csv";
	gotoxy(20, 23); cout << "19apcs1.csv";
	gotoxy(20, 24); cout << "19apcs2.csv";
	gotoxy(20, 25); cout << "20apcs1.csv";
	gotoxy(20, 26); cout << "20apcs2.csv";
	// Impossible


	int temp = 20;

	fstream f;

	

	string filepath;

	//lay danh sach lop
	filepath.clear();
	gotoxy(70, temp);
	cout << "Please enter the path of CSV file: ";
	getline(cin, filepath);
	temp++;
	f.open(filepath);

	if (!f.is_open()) {
		gotoxy(70, temp);
		cout << "The path is not existed!";
		UnNocursortype();
		Sleep(500);
		Nocursortype();
		fillBlackMenu();
		txtColor(15);
		gotoxy(132, 21);	cout << " C R E A T E   Y E A R ";
		txtColor(240);
		gotoxy(132, 24);	cout << " C R E A T E   C L A S S ";
		txtColor(15);
		gotoxy(132, 27);	cout << " C R E A T E   S E M E S T E R ";
		gotoxy(132, 30);	cout << " C R E A T E   C O U R S E ";
		return;
	}
	else {
		f.close();


		gotoxy(70, temp);
		cout << "Please enter class's name(Ex:20apcs1): ";
		getline(cin, Cname);
		temp++;



		while (createFolder(folder + "\\Classes\\" + Cname)) // lay ten lop
		{
			gotoxy(70, temp);
			cout << "Class existed";
			Sleep(500);
			gotoxy(70, temp);
			cout << "Please enter class's name(Ex:20apcs1): ";
			getline(cin, Cname);
			temp++;
		}

		f.open(folder + "\\Classes\\allClasses.csv", ios::app | ios::out);   //ghi ten lop ra file
		f << Cname << "\n";
		f.close();

		if (Class) tmpClass->next = newClass(filepath, Cname, folder + "\\Classes");
		else {
			Class = newClass(filepath, Cname, folder + "\\Classes");
		}

		autoGenerateStudentAccounts(filepath);
		autoGenerateStudentProfiles(filepath);
	}
}

// For Create Sem Mewnyu
Semesters newSemester(int currSem, date begin, date end)
{
	Semesters newSemester;
	newSemester.sem = currSem;
	dateStart = begin;
	dateEnd = end;

	return newSemester;
}
void addSemester(Semesters* semester, int currSem, date begin, date end)
{
	semester[currSem - 1] = newSemester(currSem, begin, end);
	Sem = "Sem " + to_string(currSem);
	createFolder(Schoolyear + "/Semesters/" + Sem);

	ofstream out;

	out.open("YearAndSemester.txt");
	out << Schoolyear + '\n' + Sem + '\n';
	out << dateStart.day << " " << dateStart.month << " " << dateStart.year << endl;
	out << dateEnd.day << " " << dateEnd.month << " " << dateEnd.year << endl;
	out.close();
}

// For Create Course Mewnyyyuuu
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

	newCourse->prev = nullptr;
	newCourse->next = nullptr;

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
void createFolderNFileCourse(Courses* course) // tao folder Profile.csv va Scoreboard.csv
{
	ofstream out;

	createFolder(Schoolyear + "/Semesters/" + Sem + '/' + course->courseID);

	out.open(Schoolyear + "/Semesters/" + Sem + '/' + course->courseID + "/Profile.csv");

	out << "Course ID,Course Name,Teacher Name,Num of Credits,Max Student,Weekday 1,Time 1,Weekday 2,Time 2\n";

	out << course->courseID + ',' + course->courseName + ',' + course->teacherName + ',' + to_string(course->numCredits) + ',' + to_string(course->maxStudent) + ',' + course->schedule[0].day + ',' + course->schedule[0].time + ',' + course->schedule[1].day + ',' + course->schedule[1].time + '\n';

	out.close();

	out.open(Schoolyear + "/Semesters/" + Sem + '/' + course->courseID + "/Scoreboard.csv");

	out << "No,Student ID,First Name,Last Name,Midterm,Final,Bonus,Overall\n";

	out.close();
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
void deleteCourseFolder(Courses* delCourse)
{
	string delPath = (Schoolyear + "/Semesters/" + Sem + '/' + delCourse->courseID);

	removeFile(delPath + "/Profile.csv");
	removeFile(delPath + "/Scoreboard.csv");
	removeFolder(delPath);
}

// For Create Mewnyu
void addNewCourseMain(Courses*& course)
{
	UnNocursortype();
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

	Courses* pCur = COURSE;
	while (pCur)
	{
		if (pCur->courseID == courseID)
			throw std::runtime_error("You already create a similiar course");
		pCur = pCur->next;
	}
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
		string t;
		gotoxy(70, temp);
		cout << "Enter session:\n\n";
		temp++;

		while (true)
		{
			gotoxy(70, temp);
			cout << "Day of week(From MON to SAT): "; // MON, THU
			getline(cin, t);
			temp++;
			if (t == "MON" || t == "TUE" || t == "WED" || t == "THU" || t == "FRI" || t == "SAT") {
				break;
			}
			else {
				gotoxy(70, temp);
				cout << "Please enter a valid day of week";
				temp++;
			}
		}
		schedule[i].day = t;

		while (true)
		{
			gotoxy(70, temp);
			cout << "Time(S1, S2, S3, S4): ";		//S1, S2, S3, S4
			getline(cin, t);
			temp++;
			if (t == "S1" || t == "S2" || t == "S3" || t == "S4") {
				break;
			}
			else {
				gotoxy(70, temp);
				cout << "Please enter a valid time!";
				temp++;
			}
		}
		schedule[i].time = t;
	}

	Courses* newCourse = addCourse(course, courseName, courseID, teacherName, numCredits, maxStudent, schedule);
	createFolderNFileCourse(newCourse);
	viewCourseFile(course);
	Nocursortype();
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
	cout << "You are creating new semester";

	int temp = 21;

	do {
		gotoxy(70, temp);
		cout << "Enter semester(Ex:1): ";
		cin >> currSem;
		temp++;
	} while (currSem != 1 && currSem != 2 && currSem != 3);

	gotoxy(67, temp);
	cout << "Enter course registration session starting date";
	temp++;

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

	while (!isLegalDate(begin))
	{
		temp++;
		gotoxy(67, temp);
		cout << "Enter course registration session starting date";
		temp++;
		gotoxy(70, temp);
		cout << "Date out of range!";
		temp++;
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
	}

	gotoxy(67, temp);
	cout << "Enter course registration session ending date";
	temp++;

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

	while (!isLegalDate(end))
	{
		temp++;
		gotoxy(67, temp);
		cout << "Enter course registration session ending date";
		temp++;
		gotoxy(70, temp);
		cout << "Date out of range!";
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
	}

	cin.ignore();
	addSemester(semester, currSem, begin, end);
}

// For Edit Menu
void editCourseMain(Courses*& course)
{
	txtColor(15);
	string courseID, courseName, teacherName;


	int temp = 20;
	gotoxy(70, temp);
	cout << "Enter course's ID: ";
	getline(cin, courseID);
	temp++;

	gotoxy(70, temp);
	cout << "Enter course's name: ";
	getline(cin, courseName);
	temp++;

	gotoxy(70, temp);
	cout << "Enter teacher's name: ";
	getline(cin, teacherName);
	temp++;

	//tim course de edit theo yeu cau cua staff
	Courses* edit = findCourse(course, courseID, courseName, teacherName);

	fillBlackMenu();
	txtColor(15);
	gotoxy(140, 21);	cout << " V I E W ";
	txtColor(240);
	gotoxy(140, 24);	cout << " E D I T ";
	txtColor(15);
	gotoxy(140, 27);	cout << " D E L E T E ";
	temp = 20;
	if (edit)
	{
		deleteCourseFolder(edit); 		//delete folder
		gotoxy(70, temp);
		cout << "Enter course's new infomation";
		temp++;

		gotoxy(70, ++temp);
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
			string t;
			gotoxy(70, temp);
			cout << "Enter session:\n\n";
			temp++;

			while (true)
			{
				gotoxy(70, temp);
				cout << "Day of week(From MON to SAT): "; // MON, THU
				getline(cin, edit->schedule[i].day);
				temp++;
				if (edit->schedule[i].day == "MON" || edit->schedule[i].day == "TUE" || edit->schedule[i].day == "WED" || edit->schedule[i].day == "THU" || edit->schedule[i].day == "FRI" || edit->schedule[i].day == "SAT") {
					break;
				}
				else {
					gotoxy(70, temp);
					cout << "Please enter a valid day of week";
					temp++;
				}
			}

			while (true)
			{
				gotoxy(70, temp);
				cout << "Time(S1, S2, S3, S4): ";		//S1, S2, S3, S4
				getline(cin, edit->schedule[i].time);
				temp++;
				if (edit->schedule[i].time == "S1" || edit->schedule[i].time == "S2" || edit->schedule[i].time == "S3" || edit->schedule[i].time == "S4") {
					break;
				}
				else
				{
					gotoxy(70, temp);
					cout << "Please enter a valid time!";
					temp++;
				}
			}
		}

		gotoxy(70, temp);
		cout << "Changes saved!";

		createFolderNFileCourse(edit);					//tao folder moi
		viewCourseFile(course);							//cap nhat lai file all courses
	}
	else
	{
		gotoxy(70, temp);
		cout << "There are no course match with your information!\n";
		temp++;
		Nocursortype();
		Sleep(500);
	}
}
void deleteCourseMain(Courses*& course)
{
	txtColor(15);
	string courseID, courseName, teacherName;

	int temp = 20;
	gotoxy(70, temp);
	cout << "You are deleting course:\n\n";
	temp++;

	gotoxy(70, temp);
	cout << "Enter course's ID: "; //lay course id
	getline(cin, courseID);
	temp++;

	gotoxy(70, temp);
	cout << "Enter course's name: ";	//lay course name
	getline(cin, courseName);
	temp++;

	gotoxy(70, temp);
	cout << "Enter course's name of teacher: ";		//lay course teacher
	getline(cin, teacherName);
	temp++;

	Courses* del = findCourse(course, courseID, courseName, teacherName);

	if (del)
	{
		deleteCourse(course, del);	//xoa course
		gotoxy(70, temp); cout << "Course is deleted!";
	}
	else {
		gotoxy(70, temp);
		cout << "There are no course match with your information!\n";
		temp++;
		Nocursortype();
		Sleep(500);

	}
}