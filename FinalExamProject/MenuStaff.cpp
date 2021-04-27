#include "MenuStaff.h"
#include "create.h"

void ViewYearSem() {
	txtColor(15);
	gotoxy(5, 6);	cout << "School Year: " << Schoolyear;
	gotoxy(5, 7);	cout << "Sem: " << Sem;
}

void MenuStaff(char username[], char password[], int sizeUser, int sizePass) {
	system("cls");
	logo_moodle();
	ViewYearSem();
	Nocursortype();

	keyboardShortcutMenu();

	drawBorderMenuStaff();

	txtColor(15);
	gotoxy(75, 18); cout << "H E L L O  S T A F F";

	txtColor(15);
	gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
	gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
	gotoxy(64, 24); cout << "                  V I E W                  ";
	gotoxy(64, 26); cout << "            C R E A T E   N E W            ";
	gotoxy(64, 28); cout << "          E D I T   C O U R S E S          ";
	gotoxy(64, 30); cout << "            S C O R E B O A R D            ";
	gotoxy(64, 32); cout << "               L O G   O U T               ";

	MenuStaffSettings(username, password, sizeUser, sizePass);
}

void MenuStaffSettings(char username[], char password[], int sizeUser, int sizePass) {
	int dem = 0;
	string user = convertToString(username, sizeUser);
	string pass = convertToString(password, sizePass);

	while (true)
	{
		char choice = _getch();
		txtColor(15);
		gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
		gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
		gotoxy(64, 24); cout << "                  V I E W                  ";
		gotoxy(64, 26); cout << "            C R E A T E   N E W            ";
		gotoxy(64, 28); cout << "          E D I T   C O U R S E S          ";
		gotoxy(64, 30); cout << "            S C O R E B O A R D            ";
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
				MenuStaffProfileInfo(username, password);
				ViewYearSem();
				keyboardShortcutMenu();
			}
		}
		if (dem == 2)
		{
			txtColor(240);
			gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";

			if (choice == 13)
			{
				MenuChangePasswordStaff(user, pass);
				ViewYearSem();
				keyboardShortcutMenu();
			}
		}
		if (dem == 3)
		{
			txtColor(240);
			gotoxy(64, 24); cout << "                  V I E W                  ";
			if (choice == 13)
			{
			}
		}
		if (dem == 4)
		{
			txtColor(240);
			gotoxy(64, 26); cout << "            C R E A T E   N E W            ";
			if (choice == 13)
			{
				MenuCreateNew(username, password, sizeUser, sizePass);
				ViewYearSem();
				keyboardShortcutMenu();
			}
		}
		if (dem == 5)
		{
			txtColor(240);
			gotoxy(64, 28); cout << "          E D I T   C O U R S E S          ";
			if (choice == 13)
			{
				MenuEditCourses(username, password, sizeUser, sizePass);
				ViewYearSem();
				keyboardShortcutMenu();
			}
		}
		if (dem == 6)
		{
			txtColor(240);
			gotoxy(64, 30); cout << "            S C O R E B O A R D            ";
			if (choice == 13)
			{
				MenuStaffScoreboard(username, password, sizeUser, sizePass);
				ViewYearSem();
				keyboardShortcutMenu();
			}
		}
		if (dem == 7)
		{
			txtColor(240);
			gotoxy(64, 32); cout << "               L O G   O U T               ";
			if (choice == 13)
			{
				txtColor(0);
				ViewYearSem();
				Login(username, password, sizeUser, sizePass);
			}
		}
	}
}

void MenuStaffProfileInfo(string username, string password) {
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

	in.open("Staff Profiles/" + username);

	int i = 24;
	gotoxy(70, 24);	cout << "Name: ";
	gotoxy(70, 26);	cout << "Gender: ";
	gotoxy(70, 28);	cout << "Date Of Birth: ";
	gotoxy(70, 30);	cout << "Social ID: ";
	gotoxy(70, 32);	cout << "Phone Number: ";
	while (!in.eof()) {
		getline(in, s);

		gotoxy(90, i);
		cout << s;
		i += 2;
	}

	in.close();

	while (true) {
		char choice = _getch();

		if (choice == 13 || choice == 27) {
			fillBlackMenu();
			drawBorderMenuStaff();
			txtColor(15);
			gotoxy(75, 18); cout << "H E L L O  S T A F F";

			txtColor(240);
			gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";

			txtColor(15);
			gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
			gotoxy(64, 24); cout << "                  V I E W                  ";
			gotoxy(64, 26); cout << "            C R E A T E   N E W            ";
			gotoxy(64, 28); cout << "          E D I T   C O U R S E S          ";
			gotoxy(64, 30); cout << "            S C O R E B O A R D            ";
			gotoxy(64, 32); cout << "               L O G   O U T               ";
			return;
		}
	}
}

void MenuChangePasswordStaff(string username, string& password) {
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

	in.open("Staff Accounts/" + username);

	string nameFile;
	string passFile;
	while (!in.eof()) {
		getline(in, nameFile, ',');
		getline(in, passFile);
	}

	in.close();

	string fileName = "Staff Accounts/" + username;
	remove(fileName.c_str());

	out.open("Staff Accounts/" + username);
	out << username << endl << newPassword;
	out.close();

	password = newPassword;

	Nocursortype();
	fillBlackMenu();
	drawBorderMenuStaff();
	txtColor(15);
	gotoxy(75, 18); cout << "H E L L O  S T A F F";
	gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
	txtColor(240);
	gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
	txtColor(15);
	gotoxy(64, 24); cout << "                  V I E W                  ";
	gotoxy(64, 26); cout << "            C R E A T E   N E W            ";
	gotoxy(64, 28); cout << "          E D I T   C O U R S E S          ";
	gotoxy(64, 30); cout << "            S C O R E B O A R D            ";
	gotoxy(64, 32); cout << "               L O G   O U T               ";
}

void MenuStaffView(char username[], char password[], int sizeUser, int sizePass) {
	keyboardShortcut();
	fillBlackMenu();


	int dem = 0;

	txtColor(15);
	gotoxy(135, 18);	cout << " V I E W   L I S T   O F   C L A S S E S ";
	gotoxy(135, 21);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
	gotoxy(122, 24);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
	gotoxy(121, 27);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
	gotoxy(123, 30);	cout << " U P D A T E   S T U D E N T   R E S U L T ";


}

void MenuCreateNew(char username[], char password[], int sizeUser, int sizePass) {
	keyboardShortcut();
	fillBlackMenu();

	int dem = 0;

	txtColor(15);
	gotoxy(132, 21);	cout << " C R E A T E   Y E A R ";
	gotoxy(132, 24);	cout << " C R E A T E   C L A S S ";
	gotoxy(132, 27);	cout << " C R E A T E   S E M E S T E R ";
	gotoxy(132, 30);	cout << " C R E A T E   C O U R S E ";

	while (true) {
		char choice = _getch();
		txtColor(15);
		gotoxy(132, 21);	cout << " C R E A T E   Y E A R ";
		gotoxy(132, 24);	cout << " C R E A T E   C L A S S ";
		gotoxy(132, 27);	cout << " C R E A T E   S E M E S T E R ";
		gotoxy(132, 30);	cout << " C R E A T E   C O U R S E ";

		if (choice == 80)
		{
			dem++;
			if (dem > 4)
				dem = 1;
		}

		if (choice == 72)
		{
			dem--;
			if (dem < 1)
				dem = 4;
		}

		if (choice == 27) { // ESC
			MenuStaff(username, password, sizeUser, sizePass);
			break;
		}

		if (dem == 1)
		{
			txtColor(240);
			gotoxy(132, 21);	cout << " C R E A T E   Y E A R ";
			if (choice == 13)
			{
				inputSchoolYear();

				fillBlackMenu();
				txtColor(240);
				gotoxy(132, 21);	cout << " C R E A T E   Y E A R ";
				txtColor(15);
				gotoxy(132, 24);	cout << " C R E A T E   C L A S S ";
				gotoxy(132, 27);	cout << " C R E A T E   S E M E S T E R ";
				gotoxy(132, 30);	cout << " C R E A T E   C O U R S E ";
				ViewYearSem();
			}
		}

		if (dem == 2)
		{
			txtColor(240);
			gotoxy(132, 24);	cout << " C R E A T E   C L A S S ";
			if (choice == 13)
			{
				addClass(CLASS, Schoolyear);
				
				Nocursortype();
				system("cls");
				logo_moodle();
				keyboardShortcut();
				ViewYearSem();

				txtColor(15);
				gotoxy(132, 21);	cout << " C R E A T E   Y E A R ";
				txtColor(240);
				gotoxy(132, 24);	cout << " C R E A T E   C L A S S ";
				txtColor(15);
				gotoxy(132, 27);	cout << " C R E A T E   S E M E S T E R ";
				gotoxy(132, 30);	cout << " C R E A T E   C O U R S E ";
	
			}
		}
		if (dem == 3)
		{
			txtColor(240);
			gotoxy(132, 27);	cout << " C R E A T E   S E M E S T E R ";
			if (choice == 13)
			{
				if (Schoolyear != "") {
					addNewSemesterMain(SEMESTER);

					Nocursortype();
					system("cls");
					logo_moodle();
					keyboardShortcut();
					ViewYearSem();

					txtColor(15);
					gotoxy(132, 21);	cout << " C R E A T E   Y E A R ";
					gotoxy(132, 24);	cout << " C R E A T E   C L A S S ";
					txtColor(240);
					gotoxy(132, 27);	cout << " C R E A T E   S E M E S T E R ";
					txtColor(15);
					gotoxy(132, 30);	cout << " C R E A T E   C O U R S E ";
					txtColor(15);
				
				}
				else {
					txtColor(15);
					gotoxy(70, 20);
					cout << "You must create school year first!";
					Sleep(1000);

					fillBlackMenu();
					txtColor(15);
					gotoxy(132, 21);	cout << " C R E A T E   Y E A R ";
					gotoxy(132, 24);	cout << " C R E A T E   C L A S S ";
					txtColor(240);
					gotoxy(132, 27);	cout << " C R E A T E   S E M E S T E R ";
					txtColor(15);
					gotoxy(132, 30);	cout << " C R E A T E   C O U R S E ";
					txtColor(15);
					continue;

				}
			}
		}
		if (dem == 4)
		{
			txtColor(240);
			gotoxy(132, 30);	cout << " C R E A T E   C O U R S E ";
			if (choice == 13)
			{
				if (Sem != "") {
					addNewCourseMain(COURSE);

					Nocursortype();
					fillBlackMenu();
					txtColor(15);
					gotoxy(132, 21);	cout << " C R E A T E   Y E A R ";
					gotoxy(132, 24);	cout << " C R E A T E   C L A S S ";
					gotoxy(132, 27);	cout << " C R E A T E   S E M E S T E R ";
					txtColor(240);
					gotoxy(132, 30);	cout << " C R E A T E   C O U R S E ";
					txtColor(15);
					ViewYearSem();
				}
				else {
					txtColor(15);
					gotoxy(70, 20);
					cout << "You must create semester first!";
					Sleep(1000);

					fillBlackMenu();
					txtColor(15);
					gotoxy(132, 21);	cout << " C R E A T E   Y E A R ";
					gotoxy(132, 24);	cout << " C R E A T E   C L A S S ";
					gotoxy(132, 27);	cout << " C R E A T E   S E M E S T E R ";
					txtColor(240);
					gotoxy(132, 30);	cout << " C R E A T E   C O U R S E ";
					txtColor(15);
					continue;

				}
				
			}
		}
	}
}

void MenuEditCourses(char username[], char password[], int sizeUser, int sizePass) {
	keyboardShortcut();
	fillBlackMenu();

	int dem = 0;

	txtColor(15);
	gotoxy(140, 21);	cout << " V I E W ";
	gotoxy(140, 24);	cout << " E D I T ";
	gotoxy(140, 27);	cout << " D E L E T E ";

	while (true) {
		char choice = _getch();
		txtColor(15);
		gotoxy(140, 21);	cout << " V I E W ";
		gotoxy(140, 24);	cout << " E D I T ";
		gotoxy(140, 27);	cout << " D E L E T E ";

		if (choice == 80)
		{
			dem++;
			if (dem > 3)
				dem = 1;
		}

		if (choice == 72)
		{
			dem--;
			if (dem < 1)
				dem = 3;
		}

		if (choice == 27) { // ESC
			MenuStaff(username, password, sizeUser, sizePass);
			break;
		}

		if (dem == 1)
		{
			txtColor(240);
			gotoxy(140, 21); cout << " V I E W ";
			if (choice == 13)
			{
				txtColor(15);
				gotoxy(36, 30);
				ifstream in;
				string s;

				in.open(Schoolyear + "/" + "Semesters/" + Sem + "/" + "AllCourses.txt");

				int i = 20;
				while (!in.eof()) {
					getline(in, s);

					gotoxy(5, i);
					cout << s << endl;
					i++;
				}

				in.close();
			}
		}

		if (dem == 2)
		{
			txtColor(240);
			gotoxy(140, 24); cout << " E D I T ";
			if (choice == 13)
			{
				string courseID;
				string course;
				string teacherName;

				gotoxy(100, 25);
				cout << "Please enter ID Course: ";
				cin >> courseID;
			}
		}
		if (dem == 3)
		{
			txtColor(240);
			gotoxy(140, 27); cout << " D E L E T E ";
			if (choice == 13)
			{
			}
		}
	}
}

void MenuStaffScoreboard(char username[], char password[], int sizeUser, int sizePass) {
	keyboardShortcut();
	fillBlackMenu();

	int dem = 0;

	txtColor(15);
	gotoxy(135, 18);	cout << " I M P O R T   C S V ";
	gotoxy(135, 21);	cout << " E X P O R T   C S V ";
	gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
	gotoxy(121, 27);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
	gotoxy(123, 30);	cout << " U P D A T E   S T U D E N T   R E S U L T ";

	while (true) {
		char choice = _getch();
		txtColor(15);
		gotoxy(135, 18);	cout << " I M P O R T   C S V ";
		gotoxy(135, 21);	cout << " E X P O R T   C S V ";
		gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
		gotoxy(121, 27);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
		gotoxy(123, 30);	cout << " U P D A T E   S T U D E N T   R E S U L T ";

		if (choice == 80)
		{
			dem++;
			if (dem > 5)
				dem = 1;
		}

		if (choice == 72)
		{
			dem--;
			if (dem < 1)
				dem = 5;
		}

		if (choice == 27) { // ESC
			MenuStaff(username, password, sizeUser, sizePass);
			break;
		}
		// Import CSV
		if (dem == 1)
		{
			txtColor(240);
			gotoxy(135, 18);	cout << " I M P O R T   C S V ";
			if (choice == 13)
			{
				txtColor(15);
				UnNocursortype();
				string fileName, courseID;
				ifstream f;
				gotoxy(70, 20);
				cout << "Please enter course ID: ";
				cin >> courseID;
				cout << "Please input file: ";
				cin >> fileName;
				f.open(fileName);
				int temp = 21;
				while (!f.is_open()) {
					gotoxy(70, temp);
					cout << "Please enter course ID: ";
					cin >> courseID;
					cout << "Please input file: ";
					cin >> fileName;
					f.open(fileName);
					temp++;
				}

				importScoreboardCourse(f, courseID);
				importScoreboardStudent(f, courseID);
				f.close();
				_getch();

				Nocursortype();
				fillBlackMenu();
				txtColor(240);
				gotoxy(135, 18);	cout << " I M P O R T   C S V ";
				txtColor(15);
				gotoxy(135, 21);	cout << " E X P O R T   C S V ";
				gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
				gotoxy(121, 27);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
				gotoxy(123, 30);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
			}
		}
		// Export CSV
		if (dem == 2)
		{
			txtColor(240);
			gotoxy(135, 21);	cout << " E X P O R T   C S V ";
			if (choice == 13)
			{
				txtColor(15);
				UnNocursortype();
				string courseID;
				ifstream f;
				gotoxy(70, 20);
				cout << "Please input course ID: ";
				cin >> courseID;
				f.open(Schoolyear + "/Semesters/" + Sem + "/" + courseID + "/Scoreboard.csv");
				int temp = 21;
				while (!f.is_open()) {
					gotoxy(70, temp);
					cout << "Please input course ID: ";
					cin >> courseID;
					f.open(Schoolyear + "/Semester/" + Sem + "/" + courseID + "/Scoreboard.csv");
					temp++;
				}

				exportCourseStudent(f);
				f.close();
				_getch();

				Nocursortype();
				fillBlackMenu();
				txtColor(15);
				gotoxy(135, 18);	cout << " I M P O R T   C S V ";
				txtColor(240);
				gotoxy(135, 21);	cout << " E X P O R T   C S V ";
				txtColor(15);
				gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
				gotoxy(121, 27);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
				gotoxy(123, 30);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
			}
		}
		// View Course Scoreboard
		if (dem == 3)
		{
			txtColor(240);
			gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
			if (choice == 13)
			{
				txtColor(15);
				UnNocursortype();
				string courseID;
				ifstream f;

				gotoxy(70, 20);
				cout << "Please input course ID: ";
				cin >> courseID;

				f.open(Schoolyear + "/Semesters/" + Sem + "/" + courseID + "/Scoreboard.csv");
				int temp = 21;
				while (!f.is_open()) {
					gotoxy(70, temp);
					cout << "Please input course ID: ";
					cin >> courseID;
					f.open(Schoolyear + "/Semester/" + Sem + "/" + courseID + "/Scoreboard.csv");
					temp++;
				}
				viewCourseScoreboard(f);
				f.close();
				_getch();

				Nocursortype();
				fillBlackMenu();
				gotoxy(135, 18);	cout << " I M P O R T   C S V ";
				gotoxy(135, 21);	cout << " E X P O R T   C S V ";
				txtColor(240);
				gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
				txtColor(15);
				gotoxy(121, 27);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
				gotoxy(123, 30);	cout << " U P D A T E   S T U D E N T   R E S U L T ";

				txtColor(15);
			}
		}
		// View Class Scoreboard
		if (dem == 4)
		{
			txtColor(240);
			gotoxy(121, 27);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
			if (choice == 13)
			{
				txtColor(15);
				UnNocursortype();
				string className;
				ifstream f;
				int temp = 21;

				gotoxy(70, 20);
				cout << "Please input class name: ";
				cin >> className;
				f.open(Schoolyear + "/Classes/" + className + "/allStudents.txt");

				while (!f.is_open()) {
					gotoxy(70, temp);
					cout << "Class not found";
					gotoxy(70, temp + 1);
					cout << "Please input class name: ";
					cin >> className;
					f.open(Schoolyear + "/Classes/" + className + "/allStudents.txt");
					temp+=2;
				}

				viewClassScoreboard(f, className);
				f.close();

				_getch();

				Nocursortype();
				fillBlackMenu();
				gotoxy(135, 18);	cout << " I M P O R T   C S V ";
				gotoxy(135, 21);	cout << " E X P O R T   C S V ";
				gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
				txtColor(240);
				gotoxy(121, 27);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
				txtColor(15);
				gotoxy(123, 30);	cout << " U P D A T E   S T U D E N T   R E S U L T ";

				txtColor(15);
			}
		}
		// Update Student Score
		if (dem == 5)
		{
			txtColor(240);
			gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
			if (choice == 13)
			{
				txtColor(15);
				UnNocursortype();
				string studentID, className, courseID, oldcourseDir, oldstudentDir, newcourseDir, newstudentDir;
				ifstream f1, f2;
				ofstream nf1, nf2;
				Scores newScore;
				int temp = 24;

				gotoxy(70, 20);		cout << "Please input course ID   :";	cin >> courseID;
				gotoxy(70, 21);		cout << "Please input class ID    :";	cin >> className;
				gotoxy(70, 22);		cout << "Please input student ID: :";	cin >> studentID;

				oldcourseDir = "./" + Schoolyear + "/Semesters/" + Sem + "/" + courseID + "/Scoreboard.csv";
				oldstudentDir = "./" + Schoolyear + "/Classes/" + className + "/" + studentID + "/Course " + Sem + " Scoreboard.csv";

				f1.open(oldcourseDir);
				f2.open(oldstudentDir);

				while (!(f1.is_open() && f2.is_open()))
				{
					gotoxy(70, temp);		cout << "Open file failed!";
					gotoxy(70, temp + 1);	cout << "Please input course ID   :";	cin >> courseID;
					gotoxy(70, temp + 2);	cout << "Please input class ID    :";	cin >> className;
					gotoxy(70, temp + 3);	cout << "Please input student ID: :";	cin >> studentID;

					temp += 5;

					oldcourseDir = "./" + Schoolyear + "/Semesters/" + Sem + "/" + courseID + "/Scoreboard.csv";
					oldstudentDir = "./" + Schoolyear + "/Classes/" + className + "/" + studentID + "/Course " + Sem + " Scoreboard.csv";

					f1.open(oldcourseDir);
					f2.open(oldstudentDir);
				}

				newcourseDir = "./" + Schoolyear + "/Semesters/" + Sem + "/" + courseID + "/Scoreboard_new.csv";
				newstudentDir = "./" + Schoolyear + "/Classes/" + className + "/" + studentID + "/Course " + Sem + " Scoreboard_new.csv";

				nf1.open(newcourseDir);
				nf2.open(newstudentDir);

				gotoxy(70, 20);		cout << "Please enter new score";
				gotoxy(70, 21);		cout << "New midterm score: ";	cin >> newScore.Midterm;
				gotoxy(70, 22);		cout << "New midterm score: ";	cin >> newScore.Final;
				gotoxy(70, 23);		cout << "New midterm score: ";	cin >> newScore.Bonus;
				gotoxy(70, 24);		cout << "New midterm score: ";	cin >> newScore.Total;

				// Note:
				// f1 - course, f2 - student
				// nf1 - new course, nf2 - new student
				updateStudentResult(f1, f2, nf1, nf2, studentID, courseID, newScore);

				f1.close();
				f2.close();
				nf1.close();
				nf2.close();
				_getch();

				remove(oldcourseDir.c_str());
				remove(oldstudentDir.c_str());

				rename(newcourseDir.c_str(), oldcourseDir.c_str());
				rename(newstudentDir.c_str(), oldstudentDir.c_str());


				Nocursortype();
				fillBlackMenu();
				gotoxy(135, 18);	cout << " I M P O R T   C S V ";
				gotoxy(135, 21);	cout << " E X P O R T   C S V ";
				gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
				gotoxy(121, 27);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
				txtColor(240);
				gotoxy(123, 30);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
				txtColor(15);
			}
		}
	}
}
