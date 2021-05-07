#include "MenuStudent.h"

void MenuStudent(char username[], char password[], int sizeUser, int sizePass) {
	system("cls");
	logo_moodle();
	Nocursortype();

	keyboardShortcutMenu();

	drawBorderMenuStudent();

	txtColor(15);
	gotoxy(74, 18); cout << "H E L L O  S T U D E N T";

	txtColor(15);
	gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
	gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
	gotoxy(64, 24); cout << "       E N R O L L   A   C O U R S E       ";
	gotoxy(64, 26); cout << "       R E M O V E   A   C O U R S E       ";
	gotoxy(64, 28); cout << " V I E W   E N R O L L E D   C O U R S E S ";
	gotoxy(64, 30); cout << "       V I E W   S C O R E B O A R D       ";
	gotoxy(64, 32); cout << "               L O G   O U T               ";

	MenuStudentSettings(username, password, sizeUser, sizePass);
}

void MenuStudentSettings(char username[], char password[], int sizeUser, int sizePass) {
	int dem = 0;
	string user = convertToString(username, sizeUser);
	string pass = convertToString(password, sizePass);

	// Find Student node inside Class linked list *sigh. Unelegant, smh

	Classes* pClass = CLASS;	// Find class in linked list
	Students* pStudent = nullptr;	// Find student in linked list

	string className;

	bool flag = false;	// student found flag
	while (pClass) // Iterate class list
	{
		if (flag)
			break;
		pStudent = pClass->student;
		while (pStudent)					// Iterate students
		{
			if (pStudent->ID == user)	// check StudentID
			{
				flag = true;
				break;
			}
			pStudent = pStudent->next;
		}
		pClass = pClass->next;
	}
	// pStudent is a pointer to user's Student node in linked list

	while (true)
	{
		char choice = _getch();
		txtColor(15);
		gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
		gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
		gotoxy(64, 24); cout << "       E N R O L L   A   C O U R S E       ";
		gotoxy(64, 26); cout << "       R E M O V E   A   C O U R S E       ";
		gotoxy(64, 28); cout << " V I E W   E N R O L L E D   C O U R S E S ";
		gotoxy(64, 30); cout << "       V I E W   S C O R E B O A R D       ";
		gotoxy(64, 32); cout << "               L O G   O U T               ";

		if (choice == 80)
		{
			dem++;
			if (dem > 7)
				dem = 1;
		}

		if (choice == 72)
		{
			dem--;
			if (dem < 1)
				dem = 7;
		}

		if (choice == 27) { // ESC
			system("cls");
			exit(0);
		}

		if (dem == 1)
		{
			txtColor(240);
			gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
			if (choice == 13)
			{
				MenuStudentProfileInfo(username, password);
				keyboardShortcutMenu();
			}
		}
		if (dem == 2)
		{
			txtColor(240);
			gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
			if (choice == 13)
			{
				MenuChangePasswordStudent(user, pass);
				keyboardShortcutMenu();
			}
		}
		if (dem == 3)
		{
			txtColor(240);
			gotoxy(64, 24); cout << "       E N R O L L   A   C O U R S E       ";
			if (choice == 13)
			{
				fillBlackMenu();
				UnNocursortype();
				txtColor(15);
				try
				{
					if (!COURSE)
						throw std::runtime_error("There are no courses yet!");
					string courseID;
					gotoxy(70, 20); cout << "Please enter course ID: ";
					cin >> courseID;

					Courses* pCourse = COURSE;

					flag = false;
					while (pCourse)
					{
						if (pCourse->courseID == courseID)
						{
							flag = true;
							break;
						}
						pCourse = pCourse->next;
					}
					if (!flag)
						throw std::runtime_error("Course Invalid");
					enrollACourse(*pStudent, *pCourse);
				}
				catch (const std::exception& ex)
				{
					gotoxy(70, 21);	cout << ex.what();
					_getch();
				}
				Nocursortype();
				fillBlackMenu();
				drawBorderMenuStudent();
				txtColor(15);
				gotoxy(74, 18); cout << "H E L L O  S T U D E N T";
				gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
				gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
				txtColor(240);
				gotoxy(64, 24); cout << "       E N R O L L   A   C O U R S E       ";
				txtColor(15);
				gotoxy(64, 26); cout << "       R E M O V E   A   C O U R S E       ";
				gotoxy(64, 28); cout << " V I E W   E N R O L L E D   C O U R S E S ";
				gotoxy(64, 30); cout << "       V I E W   S C O R E B O A R D       ";
				gotoxy(64, 32); cout << "               L O G   O U T               ";
			}
		}

		// Not tested
		if (dem == 4)
		{
			txtColor(240);
			gotoxy(64, 26); cout << "       R E M O V E   A   C O U R S E       ";
			if (choice == 13)
			{
				UnNocursortype();
				fillBlackMenu();
				txtColor(15);
				try
				{
					Courses* pCourse = COURSE;

					if (!pStudent->courseStudent)
						throw std::runtime_error("You can't delete a non-existent thing");
					string courseID;
					gotoxy(70, 20); cout << "Please enter course ID you want to reverse enroll: ";
					getline(cin, courseID);

					flag = false;
					while (pCourse)
					{
						if (pCourse->courseID == courseID)
						{
							flag = true;
							break;
						}
						pCourse = pCourse->next;
					}
					if (!flag)
						throw std::runtime_error("Course Invalid");

					removeACourse(pStudent, pCourse);
				}
				catch (const std::exception& ex)
				{
					gotoxy(70, 21);	cout << ex.what();
					_getch();
				}
				Nocursortype();
				fillBlackMenu();
				drawBorderMenuStudent();
				txtColor(15);
				gotoxy(74, 18); cout << "H E L L O  S T U D E N T";
				gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
				gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
				gotoxy(64, 24); cout << "       E N R O L L   A   C O U R S E       ";
				txtColor(240);
				gotoxy(64, 26); cout << "       R E M O V E   A   C O U R S E       ";
				txtColor(15);
				gotoxy(64, 28); cout << " V I E W   E N R O L L E D   C O U R S E S ";
				gotoxy(64, 30); cout << "       V I E W   S C O R E B O A R D       ";
				gotoxy(64, 32); cout << "               L O G   O U T               ";
			}
		}

		// Not tested
		if (dem == 5)
		{
			txtColor(240);
			gotoxy(64, 28); cout << " V I E W   E N R O L L E D   C O U R S E S ";
			if (choice == 13)
			{
				UnNocursortype();
				fillBlackMenu();
				txtColor(15);
				if (pStudent)
				{
					if (pStudent->courseStudent)
						viewEnrolledCourses(pStudent);
					else
					{
						gotoxy(70, 20); cout << "You haven't enrolled any course yet!";
						_getch();
					}
					Nocursortype();
					fillBlackMenu();
					drawBorderMenuStudent();
					txtColor(15);
					gotoxy(74, 18); cout << "H E L L O  S T U D E N T";
					gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
					gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
					gotoxy(64, 24); cout << "       E N R O L L   A   C O U R S E       ";
					gotoxy(64, 26); cout << "       R E M O V E   A   C O U R S E       ";
					txtColor(240);
					gotoxy(64, 28); cout << " V I E W   E N R O L L E D   C O U R S E S ";
					txtColor(15);
					gotoxy(64, 30); cout << "       V I E W   S C O R E B O A R D       ";
					gotoxy(64, 32); cout << "               L O G   O U T               ";
				}
			}
		}


		//Not tested
		if (dem == 6)
		{
			txtColor(240);
			gotoxy(64, 30); cout << "       V I E W   S C O R E B O A R D       ";
			if (choice == 13)
			{
				try
				{

					txtColor(15);
					UnNocursortype();
					ifstream f;
					string className = checkStudentClass(user);
					f.open(Schoolyear + "/Classes/" + className + "/" + user + "/Course " + Sem + " Scoreboard.csv");
					if (!f.is_open())
						throw std::runtime_error("Can't open user scoreboard");
					viewOwnScoreboard(f, 22);

				}
				catch (std::exception& ex)
				{
					gotoxy(70, 20);	cout << ex.what();
					_getch();
				}
				Nocursortype();
				fillBlackMenu();
				txtColor(15);
				gotoxy(74, 18); cout << "H E L L O  S T U D E N T";
				gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
				gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
				gotoxy(64, 24); cout << "       E N R O L L   A   C O U R S E       ";
				gotoxy(64, 26); cout << "       R E M O V E   A   C O U R S E       ";
				gotoxy(64, 28); cout << " V I E W   E N R O L L E D   C O U R S E S ";
				txtColor(240);
				gotoxy(64, 30); cout << "       V I E W   S C O R E B O A R D       ";
				txtColor(15);
				gotoxy(64, 32); cout << "               L O G   O U T               ";
			}
		}
		if (dem == 7)
		{
			txtColor(240);
			gotoxy(64, 32); cout << "               L O G   O U T               ";
			if (choice == 13)
			{
				txtColor(0);
				Login(username, password, sizeUser, sizePass);
			}
		}
	}
}

void MenuStudentProfileInfo(string username, string password) {
	keyboardShortcut();
	fillBlackMenu();

	txtColor(15);
	gotoxy(70, 15);	cout << " _____            __ _ _      ";
	gotoxy(70, 16);	cout << "|  __ \\          / _(_) |     ";
	gotoxy(70, 17);	cout << "| |__) | __ ___ | |_ _| | ___ ";
	gotoxy(70, 18);	cout << "|  ___/ '__/ _ \\|  _| | |/ _ \\";
	gotoxy(70, 19);	cout << "| |   | | | (_) | | | | |  __/";
	gotoxy(70, 20);	cout << "|_|   |_|  \\___/|_| |_|_|\\___|";

	txtColor(15);
	ifstream in;
	string s;

	in.open("Student Profiles/" + username);

	string ignore;
	string studentID;
	string lastName;
	string firstName;
	string gender;
	string dob;
	string socialID;

	while (in.peek() != EOF) {
		getline(in, ignore);
		getline(in, studentID);
		getline(in, lastName);
		getline(in, firstName);
		getline(in, gender);
		getline(in, dob);
		getline(in, socialID);
	}
	in.close();

	gotoxy(70, 24);	cout << "Name: " << lastName << " " << firstName;
	gotoxy(70, 26);	cout << "Student ID: " << studentID;
	gotoxy(70, 28);	cout << "Gender: " << gender;
	gotoxy(70, 30);	cout << "Date Of Birth: " << dob;
	gotoxy(70, 32);	cout << "Social ID: " << socialID;

	while (true) {
		char choice = _getch();

		if (choice == 13 || choice == 27) {
			fillBlackMenu();
			drawBorderMenuStudent();

			txtColor(15);
			gotoxy(74, 18); cout << "H E L L O  S T U D E N T";

			txtColor(240);
			gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";

			txtColor(15);
			gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
			gotoxy(64, 24); cout << "       E N R O L L   A   C O U R S E       ";
			gotoxy(64, 26); cout << "       R E M O V E   A   C O U R S E       ";
			gotoxy(64, 28); cout << " V I E W   E N R O L L E D   C O U R S E S ";
			gotoxy(64, 30); cout << "            S C O R E B O A R D            ";
			gotoxy(64, 32); cout << "               L O G   O U T               ";
			return;
		}
	}
}

void MenuChangePasswordStudent(string username, string& password) {
	keyboardShortcut();
	fillBlackMenu();
	UnNocursortype();
	txtColor(15);

	string oldPassword;
	string newPassword;
	string newPasswordAgain;
	bool check;

	int temp = 20;
	do {
		gotoxy(70, temp);
		cout << "Old password: ";
		cin >> oldPassword;

		for (int i = 0; i < oldPassword.size(); ++i) {
			if (oldPassword.size() > password.size())
				check = false;
			else if (oldPassword.size() < password.size())
				check = false;
			else if (oldPassword[i] != password[i])
				check = false;
			else
				check = true;
		}
		temp++;
	} while (check == false);

	gotoxy(70, temp);
	cout << "New password: ";
	cin >> newPassword;
	temp++;

	do {
		gotoxy(70, temp);
		cout << "Please input your new password again: ";
		cin >> newPasswordAgain;
		temp++;
	} while (newPassword.compare(newPasswordAgain) != 0);

	ifstream in;
	ofstream out;

	in.open("Student Accounts/" + username);

	string nameFile;
	string passFile;
	while (!in.eof()) {
		getline(in, nameFile, ',');
		getline(in, passFile);
	}

	in.close();

	string fileName = "Student Accounts/" + username;
	remove(fileName.c_str());

	out.open("Student Accounts/" + username);
	out << username << endl << newPassword;
	out.close();

	password = newPassword;

	Nocursortype();
	fillBlackMenu();
	drawBorderMenuStudent();

	txtColor(15);
	gotoxy(74, 18); cout << "H E L L O  S T U D E N T";
	gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
	txtColor(240);
	gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
	txtColor(15);
	gotoxy(64, 24); cout << "       E N R O L L   A   C O U R S E       ";
	gotoxy(64, 26); cout << "       R E M O V E   A   C O U R S E       ";
	gotoxy(64, 28); cout << " V I E W   E N R O L L E D   C O U R S E S ";
	gotoxy(64, 30); cout << "       V I E W   S C O R E B O A R D       ";
	gotoxy(64, 32); cout << "               L O G   O U T               ";
}