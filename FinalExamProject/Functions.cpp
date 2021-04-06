#include "Header.h"

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

void readClassCSV(ifstream& classList, Student& student) // Assume storing student as doubly linked list
{
    // Temp function only read one row for a single student
    string temp;
    // Read the Data from the file as String Vector
    getline(classList, temp, ',');
    student.no = stoi(temp);
    getline(classList, temp, ',');
    student.ID = stoi(temp);
    getline(classList, temp, ',');
    student.firstName = temp;
    getline(classList, temp, ',');
    student.lastName = temp;
    getline(classList, temp, ',');
    student.gender = temp;
    getline(classList, temp, ',');
    student.dateOfBirth = temp;
    getline(classList, temp);
    student.socialID = temp;
}
