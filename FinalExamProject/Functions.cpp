#include "Functions.h"
/*
void Nocursortype() {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;

	// bigger bolder
	gotoxy(63, 21);
	for (int i = 0; i < 45; ++i)
		cout << char(220);

	for (int i = 22; i < 40; ++i) {
		gotoxy(63, i);
		cout << char(219);
	}

	for (int i = 22; i < 40; ++i) {
		gotoxy(107, i);
		cout << char(219);
	}

	gotoxy(63, 40);
	for (int i = 0; i < 45; ++i)
		cout << char(223);

	gotoxy(73, 22);	cout << " _    ___   ___ ___ _  _ ";
	gotoxy(73, 23);	cout << "| |  / _ \\ / __|_ _| \\| |";
	gotoxy(73, 24);	cout << "| |_| (_) | (_ || || .` |";
	gotoxy(73, 25);	cout << "|____\\___/ \\___|___|_|\\_|";

	txtColor(15);
	//smaller bolder 1 ( Username )
	gotoxy(68, 28);	cout << "USERNAME:";

	gotoxy(73, 29);
	for (int i = 0; i < 27; ++i)
		cout << char(205);

	gotoxy(73, 29); cout << char(201);
	gotoxy(99, 29); cout << char(187);
	gotoxy(73, 30); cout << char(186);
	gotoxy(99, 30); cout << char(186);

	gotoxy(73, 31);
	for (int i = 0; i < 27; ++i)
		cout << char(205);

	gotoxy(73, 31); cout << char(200);
	gotoxy(99, 31); cout << char(188);

	//smaller bolder 2 ( Password )
	gotoxy(68, 33);	cout << "PASSWORD:";

	gotoxy(73, 34);
	for (int i = 0; i < 27; ++i)
		cout << char(205);

	gotoxy(73, 34); cout << char(201);
	gotoxy(99, 34); cout << char(187);
	gotoxy(73, 35); cout << char(186);
	gotoxy(99, 35); cout << char(186);

	gotoxy(73, 36);
	for (int i = 0; i < 27; ++i)
		cout << char(205);

	gotoxy(73, 36); cout << char(200);
	gotoxy(99, 36); cout << char(188);


	// input here
	gotoxy(75, 30);
	string a;
	cin >> a;

	gotoxy(75, 35);
	string b;
	cin >> b;

	bool check = false;

	if (check == true) {
		system("cls");
		logo_moodle();
	}
	else {
		txtColor(12);
		gotoxy(78, 38); cout << "*** INVALID ***";
		gotoxy(78, 41);
		txtColor(15);
	}
}
*/

void createStudent(ifstream& classList, Students& student) // Read CSV file for student's info
{
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
		pCur = readClassCSV(file, pCur);
		pCur->next = nullptr;
	}
	file.close();
}

void exportCourseStudent(CoursesStudent Course)
{
	ofstream file(Course.courseName + "_List_of_Students.csv");
	string colName[] = { "No", "Student ID", "Student Full Name", "Total Mark", "Final Mark", "Midterm Mark", "Other Mark" };
	for (int i = 0; i < 7; i++)
		file << colName[i] << ",";
	file << endl;
	for (int i = 0; i < sizeof(Course.studentList) / sizeof(Course.studentList[0]); ++i)
	{
		file << i + 1 << ",";
		file << Course.studentList[i].ID << ",";
		file << Course.studentList[i].lastName << Course.studentList[i].firstName << ",";
		file << "," << "," << "," << "," << endl;
	}
}