#include "MenuStaff.h"
#include "UI.h"
#include "InputLogin.h"

void MenuStaff(char username[], char password[], int sizeUser, int sizePass) {
	system("cls");
	logo_moodle();
	Nocursortype();

	keyboardShortcutMenu();

	drawBorderMenuStaff();

	txtColor(15);
	gotoxy(75, 18); cout << "H E L L O  S T A F F";

	txtColor(15);
	gotoxy(67, 20); cout << "P R O F I L E   I N F O R M A T I O N";
	gotoxy(71, 22); cout << "C H A N G E   P A S S W O R D";
	gotoxy(73, 24); cout << "V I E W   S T U D E N T S"; // VIEW STUDENTS IN CLASSES IN COURSES
	gotoxy(76, 26); cout << "C R E A T E   N E W"; // CREATE SCHOOLYEAR(CLASS), SEMESTER, COURSE
	gotoxy(74, 28); cout << "E D I T   C O U R S E S"; // IMPORT COURSES FILE EXISTS AND THEN STAFF CAN ENTER THE COURSE ID AND EDIT
	gotoxy(76, 30); cout << "S C O R E B O A R D"; // VIEW AND EDIT INCLUDES 1. VIEW SCORES OF 1 COURSE
	gotoxy(79, 32); cout << "L O G   O U T";				// 2. EDIT STUDENT SCORE IN COURSE, 3. VIEW ALL SCORES OF ALL COURSES

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
		gotoxy(64, 24); cout << "         V I E W   S T U D E N T S         ";
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
				keyboardShortcutMenu();

			}
		}
		if (dem == 3)
		{
			txtColor(240);
			gotoxy(64, 24); cout << "         V I E W   S T U D E N T S         ";
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

			}
		}
		if (dem == 5)
		{
			txtColor(240);
			gotoxy(64, 28); cout << "          E D I T   C O U R S E S          ";
			if (choice == 13)
			{
				MenuEditCourses(username, password, sizeUser, sizePass);
				keyboardShortcutMenu();
			}
		}
		if (dem == 6)
		{
			txtColor(240);
			gotoxy(64, 30); cout << "            S C O R E B O A R D            ";
			if (choice == 13)
			{

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
			gotoxy(64, 24); cout << "         V I E W   S T U D E N T S         ";
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
	gotoxy(64, 24); cout << "         V I E W   S T U D E N T S         ";
	gotoxy(64, 26); cout << "            C R E A T E   N E W            ";
	gotoxy(64, 28); cout << "          E D I T   C O U R S E S          ";
	gotoxy(64, 30); cout << "            S C O R E B O A R D            ";
	gotoxy(64, 32); cout << "               L O G   O U T               ";
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

				in.open(schoolYear + "/" + "Semesters/" + sem + "/" + "AllCourses.txt");

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