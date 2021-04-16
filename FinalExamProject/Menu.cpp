#include "UI.h"

void keyboardShortcutMenu() {

	txtColor(15);
	gotoxy(130, 6);  cout << "K E Y B O A R D   S H O R C U T";
	gotoxy(130, 8);  cout << "P R E S S    ^    T O   U P";
	gotoxy(130, 9);  cout << "P R E S S    v    T O   D O W N";
	gotoxy(130, 10); cout << "P R E S S   ESC   T O   E X I T ";

	txtColor(240);
	gotoxy(141, 8); cout << "  ^  ";
	gotoxy(141, 9); cout << "  v  ";
	gotoxy(141, 10); cout << " ESC ";
	txtColor(15);

}

void keyboardShortcut() {
	txtColor(240);
	gotoxy(141, 8); cout << "  ^  ";
	gotoxy(141, 9); cout << "  v  ";
	gotoxy(141, 10); cout << " ESC ";

	txtColor(15);
	gotoxy(130, 6);  cout << "K E Y B O A R D   S H O R C U T";
	gotoxy(130, 8);  cout << "P R E S S    ^    T O   U P";
	gotoxy(130, 9);  cout << "P R E S S    v    T O   D O W N";
	gotoxy(130, 10); cout << "P R E S S   ESC   T O   B A C K ";

}

void Login(char username[], char password[], int sizeUser, int sizePass) {
	system("cls");
	logo_moodle();
	loginUI();

	while (true) {
		fillBlackLogin();
		inputUsername(username, sizeUser);
		inputPassword(password, sizePass);

		if (checkValidUsernameAndPasswordStaff(username, password) == true) {
			break;
		}
		if (checkValidUsernameAndPasswordStudent(username, password) == true) {
			break;
		}

		else {
			txtColor(12);
			gotoxy(66, 38); cout << " *** INCORRECT USERNAME OR PASSWORD ***" << endl;
			Nocursortype();
			Sleep(700);
			txtColor(15);
		}

	}
	if (checkValidUsernameAndPasswordStaff(username, password) == true) {
		system("cls");
		logo_moodle();
		menuStaff(username, password, sizeUser, sizePass);
	}

	if (checkValidUsernameAndPasswordStudent(username, password) == true) {
		system("cls");
		logo_moodle();
		menuStudent(username, password, sizeUser, sizePass);
	}
}

void menuStaff(char username[], char password[], int sizeUser, int sizePass) {
	system("cls");
	logo_moodle();
	Nocursortype();

	keyboardShortcutMenu();

	txtColor(14);
	gotoxy(63, 16);
	for (int i = 0; i < 45; ++i)
		cout << char(219);

	for (int i = 17; i < 35; ++i) {
		gotoxy(63, i);
		cout << char(219);
	}

	for (int i = 17; i < 35; ++i) {
		gotoxy(107, i);
		cout << char(219);
	}

	gotoxy(63, 34);
	for (int i = 0; i < 45; ++i)
		cout << char(223);

	txtColor(240);
	gotoxy(73, 18); cout << char(32);
	gotoxy(96, 18); cout << char(32);

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

	menuStaffSettings(username, password, sizeUser, sizePass);
}

void menuStaffSettings(char username[], char password[], int sizeUser, int sizePass) {
	int dem = 0;
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

			}
		}
		if (dem == 2)
		{
			txtColor(240);
			gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
			if (choice == 13)
			{

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

void menuStudent(char username[], char password[], int sizeUser, int sizePass) {
	system("cls");
	logo_moodle();
	Nocursortype();

	keyboardShortcutMenu();

	txtColor(14);
	gotoxy(63, 16);
	for (int i = 0; i < 45; ++i)
		cout << char(219);

	for (int i = 17; i < 33; ++i) {
		gotoxy(63, i);
		cout << char(219);
	}

	for (int i = 17; i < 33; ++i) {
		gotoxy(107, i);
		cout << char(219);
	}

	gotoxy(63, 32);
	for (int i = 0; i < 45; ++i)
		cout << char(223);

	txtColor(240);
	gotoxy(72, 18); cout << char(32);
	gotoxy(99, 18); cout << char(32);

	txtColor(15);
	gotoxy(74, 18); cout << "H E L L O  S T U D E N T";

	txtColor(15);
	gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
	gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
	gotoxy(64, 24); cout << "          E D I T   C O U R S E S          ";
	gotoxy(64, 26); cout << "          V I E W   C O U R S E S          ";
	gotoxy(64, 28); cout << "            S C O R E B O A R D            ";
	gotoxy(64, 30); cout << "               L O G   O U T               ";

	menuStudentSettings(username, password, sizeUser, sizePass);
}

void menuStudentSettings(char username[], char password[], int sizeUser, int sizePass) {
	int dem = 0;
	while (true)
	{
		char choice = _getch();
		txtColor(15);
		gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
		gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
		gotoxy(64, 24); cout << "          E D I T   C O U R S E S          ";
		gotoxy(64, 26); cout << "          V I E W   C O U R S E S          ";
		gotoxy(64, 28); cout << "            S C O R E B O A R D            ";
		gotoxy(64, 30); cout << "               L O G   O U T               ";

		if (choice == 80)
		{
			dem++;
			if (dem > 6)
				dem = 1;
		}

		if (choice == 72)
		{
			dem--;
			if (dem < 1)
				dem = 6;
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
				return;
			}
		}
		if (dem == 2)
		{
			txtColor(240);
			gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
			if (choice == 13)
			{

			}
		}
		if (dem == 3)
		{
			txtColor(240);
			gotoxy(64, 24); cout << "          E D I T   C O U R S E S          ";
			if (choice == 13)
			{

			}
		}
		if (dem == 4)
		{
			txtColor(240);
			gotoxy(64, 26); cout << "          V I E W   C O U R S E S          ";
			if (choice == 13)
			{

			}
		}
		if (dem == 5)
		{
			txtColor(240);
			gotoxy(64, 28); cout << "            S C O R E B O A R D            ";
			if (choice == 13)
			{

			}
		}
		if (dem == 6)
		{
			txtColor(240);
			gotoxy(64, 30); cout << "               L O G   O U T               ";
			if (choice == 13)
			{
				txtColor(0);
				Login(username, password, sizeUser, sizePass);
			}
		}
	}
}

