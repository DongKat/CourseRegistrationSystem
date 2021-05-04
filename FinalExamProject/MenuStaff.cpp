#include "MenuStaff.h"

void ViewYearSem()
{
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
	gotoxy(64, 28); cout << "               C O U R S E S               ";
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
		gotoxy(64, 28); cout << "               C O U R S E S               ";
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
				MenuStaffView(username, password, sizeUser, sizePass);
				ViewYearSem();
				keyboardShortcutMenu();
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
			gotoxy(64, 28); cout << "               C O U R S E S               ";
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

	try
	{
		in.open("Staff Profiles/" + username);
		if (!in.is_open())
			throw std::runtime_error("Staff " + username + "'s Profile not found. Please insert new one in ./Staff Profiles/");
		int i = 24;
		gotoxy(70, 24);	cout << "Name: ";
		gotoxy(70, 26);	cout << "Gender: ";
		gotoxy(70, 28);	cout << "Date Of Birth: ";
		gotoxy(70, 30);	cout << "Social ID: ";
		gotoxy(70, 32);	cout << "Phone Number: ";
		while (in.peek() != EOF)
		{
			getline(in, s);
			gotoxy(90, i);	cout << s;
			i += 2;
		}
		in.close();
	}
	catch (exception& ex)
	{
		gotoxy(70, 25); cout << ex.what();
	}

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
			gotoxy(64, 28); cout << "               C O U R S E S               ";
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
	bool check = false;

	int temp = 20;
	gotoxy(70, temp);
	cout << "Old password: ";	cin >> oldPassword;
	while (!check)
	{
		for (int i = 0; i < oldPassword.size(); ++i)
		{
			if (oldPassword.size() > password.size())
				check = false;
			else if (oldPassword.size() < password.size())
				check = false;
			else if (oldPassword[i] != password[i])
				check = false;
			else
				check = true;
		}
		if (check) break;
		gotoxy(70, ++temp);
		cout << "Old password wrong!";
		gotoxy(70, temp += 2);
		cout << "Old password: ";	cin >> oldPassword;
	}

	while (true)
	{
		gotoxy(70, ++temp);	cout << "New password: ";
		cin >> newPassword;
		gotoxy(70, ++temp);	cout << "Please input your new password again: ";
		cin >> newPasswordAgain;
		if (newPassword.compare(newPasswordAgain) != 0)
		{
			gotoxy(70, ++temp);	cout << "Password doesn't match. Please enter again.";
			temp++;
		}
		else
			break;
	}
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
	gotoxy(64, 28); cout << "               C O U R S E S               ";
	gotoxy(64, 30); cout << "            S C O R E B O A R D            ";
	gotoxy(64, 32); cout << "               L O G   O U T               ";
}

void MenuStaffView(char username[], char password[], int sizeUser, int sizePass) {
	keyboardShortcut();
	fillBlackMenu();

	int dem = 0;
	int temp = 22;

	txtColor(15);
	gotoxy(127, 20);	cout << " V I E W   L I S T   O F   C L A S S E S ";

	gotoxy(126, 23);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
	gotoxy(126, 24);	cout << "            I N   A   C L A S S            ";

	gotoxy(127, 27);	cout << " V I E W   L I S T   O F   C O U R S E S ";

	gotoxy(126, 30);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
	gotoxy(126, 31);	cout << "           I N   A   C O U R S E           ";

	while (true) {
		char choice = _getch();
		txtColor(15);
		gotoxy(127, 20);	cout << " V I E W   L I S T   O F   C L A S S E S ";

		gotoxy(126, 23);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
		gotoxy(126, 24);	cout << "            I N   A   C L A S S            ";

		gotoxy(127, 27);	cout << " V I E W   L I S T   O F   C O U R S E S ";

		gotoxy(126, 30);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
		gotoxy(126, 31);	cout << "           I N   A   C O U R S E           ";

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

		if (choice == 27) // ESC
		{
			MenuStaff(username, password, sizeUser, sizePass);
			break;
		}

		if (dem == 1)	//===============================================================================================================
		{
			txtColor(240);
			gotoxy(127, 20);	cout << " V I E W   L I S T   O F   C L A S S E S ";
			if (choice == 13)
			{
				try
				{
					UnNocursortype();
					txtColor(15);
					viewAllClass();
				}
				catch (const std::exception& ex)
				{
					gotoxy(70, temp); cout << ex.what();
					Sleep(500);
				}
				_getch();
				fillBlackMenu();
				Nocursortype();
				txtColor(15);

				txtColor(240);
				gotoxy(127, 20);	cout << " V I E W   L I S T   O F   C L A S S E S ";
				txtColor(15);

				gotoxy(126, 23);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
				gotoxy(126, 24);	cout << "            I N   A   C L A S S            ";

				gotoxy(127, 27);	cout << " V I E W   L I S T   O F   C O U R S E S ";

				gotoxy(126, 30);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
				gotoxy(126, 31);	cout << "           I N   A   C O U R S E           ";
			}
		}

		if (dem == 2)	//===============================================================================================================
		{
			txtColor(240);
			gotoxy(126, 23);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
			gotoxy(126, 24);	cout << "            I N   A   C L A S S            ";
			if (choice == 13)
			{
				try
				{
					txtColor(15);
					if (!CLASS)
						throw std::runtime_error("There are no classes yet!");

					UnNocursortype();
					string className;
					Classes* pCur = CLASS;
					gotoxy(70, 20);	cout << "Please enter class name: ";
					cin >> className;

					bool flag = false;
					while (pCur)
					{
						if (pCur->className == className)
						{
							flag = true;
							break;
						}
						pCur = pCur->next;
					}
					if (!flag)
						throw std::runtime_error("Class Invalid");

					viewAllStudentInClass(pCur);
				}
				catch (const std::exception& ex)
				{
					gotoxy(70, temp); cout << ex.what();
					Sleep(500);
				}
				_getch();
				fillBlackMenu();
				Nocursortype();
				txtColor(15);

				gotoxy(127, 20);	cout << " V I E W   L I S T   O F   C L A S S E S ";

				txtColor(240);
				gotoxy(126, 23);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
				gotoxy(126, 24);	cout << "            I N   A   C L A S S            ";
				txtColor(15);

				gotoxy(127, 27);	cout << " V I E W   L I S T   O F   C O U R S E S ";

				gotoxy(126, 30);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
				gotoxy(126, 31);	cout << "           I N   A   C O U R S E           ";
			}
		}

		if (dem == 3)	//===============================================================================================================
		{
			txtColor(240);
			gotoxy(127, 27);	cout << " V I E W   L I S T   O F   C O U R S E S ";
			if (choice == 13)
			{
				try
				{
					UnNocursortype();
					txtColor(15);
					viewAllCourse();
				}
				catch (const std::exception& ex)
				{
					gotoxy(70, temp); cout << ex.what();
					Sleep(500);
				}
				_getch();
				fillBlackMenu();
				Nocursortype();
				txtColor(15);

				gotoxy(127, 20);	cout << " V I E W   L I S T   O F   C L A S S E S ";

				gotoxy(126, 23);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
				gotoxy(126, 24);	cout << "            I N   A   C L A S S            ";

				txtColor(240);
				gotoxy(127, 27);	cout << " V I E W   L I S T   O F   C O U R S E S ";
				txtColor(15);

				gotoxy(126, 30);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
				gotoxy(126, 31);	cout << "           I N   A   C O U R S E           ";
			}
		}

		if (dem == 4)	//===============================================================================================================
		{
			txtColor(240);
			gotoxy(126, 30);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
			gotoxy(126, 31);	cout << "           I N   A   C O U R S E           ";
			if (choice == 13)
			{
				try
				{
					UnNocursortype();
					txtColor(15);
					if (!COURSE)
						throw std::runtime_error("There are no courses yet!");

					UnNocursortype();
					string courseID;
					Courses* pCur = COURSE;
					gotoxy(70, 20);	cout << "Please enter course ID: ";
					cin >> courseID;

					bool flag = false;
					while (pCur)
					{
						if (pCur->courseID == courseID)
						{
							flag = true;
							break;
						}
						pCur = pCur->next;
					}
					if (!flag)
						throw std::runtime_error("Course Invalid");
					viewAllStudentInCourse(pCur);
				}
				catch (const std::exception& ex)
				{
					gotoxy(70, temp); cout << ex.what();
					Sleep(500);
				}
				_getch();
				fillBlackMenu();
				Nocursortype();
				txtColor(15);

				gotoxy(127, 20);	cout << " V I E W   L I S T   O F   C L A S S E S ";

				gotoxy(126, 23);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
				gotoxy(126, 24);	cout << "            I N   A   C L A S S            ";

				gotoxy(127, 27);	cout << " V I E W   L I S T   O F   C O U R S E S ";

				txtColor(240);
				gotoxy(126, 30);	cout << " V I E W   L I S T   O F   S T U D E N T S ";
				gotoxy(126, 31);	cout << "           I N   A   C O U R S E           ";
				txtColor(15);
			}
		}
		//===========================================================================================================================
	}
}

void MenuCreateNew(char username[], char password[], int sizeUser, int sizePass) {
	keyboardShortcut();
	fillBlackMenu();

	int dem = 0;

	bool schoolYearFlag, semesterFlag;
	schoolYearFlag = semesterFlag = false;

	if (Schoolyear == "")
		schoolYearFlag = true;
	if (Sem == "")
		semesterFlag = true;

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

		if (dem == 1)	//===============================================================================================================
		{
			txtColor(240);
			gotoxy(132, 21);	cout << " C R E A T E   Y E A R ";
			if (choice == 13)
			{
				if (!schoolYearFlag)
				{
					txtColor(15);
					gotoxy(70, 20); cout << "Are you sure you want to end current schoolyear?";
					while (true)
					{
						int count = 0;
						txtColor(15);
						if (choice == 75)
						{
							count--;
							if (count > 2)
								count = 1;
						}

						if (choice == 77)
						{
							count++;
							if (count < 1)
								count = 2;
						}
						if (count == 1)
						{
							txtColor(240);
							gotoxy(60, 10); cout << "YES,YES,YES";
							if (choice == 13)
							{
								txtColor(15);
								inputSchoolYear();
								break;
							}
						}
						if (count == 2)
						{
							txtColor(240);
							gotoxy(60, 25); cout << "NO, NO, NO";
							if (choice == 13)
							{
								break;
							}
						}
					}
				}
				else
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

		if (dem == 2)	//===============================================================================================================
		{
			txtColor(240);
			gotoxy(132, 24);	cout << " C R E A T E   C L A S S ";
			if (choice == 13)
			{
				UnNocursortype();
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
		if (dem == 3)	//===============================================================================================================
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
		if (dem == 4)	//===============================================================================================================
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
		//=================================================================================================================================
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
				if (Sem == "") {
					txtColor(15);
					gotoxy(70, 20);
					cout << "You must create semester first!";
					Sleep(1000);
					gotoxy(70, 20);
					txtColor(0);
					cout << "You must create semester first!";
					txtColor(15);
					continue;
				}

				Nocursortype();
				fillBlackMenu();
				txtColor(240);
				gotoxy(140, 21);	cout << " V I E W ";
				txtColor(15);
				gotoxy(140, 24);	cout << " E D I T ";
				gotoxy(140, 27);	cout << " D E L E T E ";


				ifstream in;
				string courseID;
				string courseName;
				string teacherName;
				string ignore_line;
				in.open(Schoolyear + "/" + "Semesters/" + Sem + "/" + "AllCourses.csv");

				int i = 18;
				int n = 1;

				gotoxy(45, 17);	cout << "Course's ID";
				gotoxy(60, 17);	cout << "Course's Name";
				gotoxy(105, 17);	cout << "Teacher's Name";

				getline(in, ignore_line);
				while (!in.eof()) {
					getline(in, courseID, ',');
					getline(in, courseName, ',');
					getline(in, teacherName);

					gotoxy(45, i);
					cout << courseID;
					gotoxy(60, i);
					cout << courseName;
					gotoxy(105, i);
					cout << teacherName;
					i++;
				}

				/*txtColor(0);
				for (int j = 44; j < 120; ++j) {
					gotoxy(j, i - 1);
					cout << char(32);
				}*/

				txtColor(15);

				in.close();
			}
		}

		if (dem == 2)
		{
			txtColor(240);
			gotoxy(140, 24); cout << " E D I T ";
			if (choice == 13)
			{
				if (Sem == "") {
					txtColor(15);
					gotoxy(70, 20);
					cout << "You must create semester first!";
					Sleep(1000);
					gotoxy(70, 20);
					txtColor(0);
					cout << "You must create semester first!";
					txtColor(15);
					continue;
				}
				Nocursortype();
				fillBlackMenu();
				txtColor(15);
				gotoxy(140, 21);	cout << " V I E W ";
				txtColor(240);
				gotoxy(140, 24);	cout << " E D I T ";
				txtColor(15);
				gotoxy(140, 27);	cout << " D E L E T E ";

				editCourseMain(COURSE);
			}
		}
		if (dem == 3)
		{
			txtColor(240);
			gotoxy(140, 27); cout << " D E L E T E ";
			if (choice == 13)
			{
				if (Sem == "") {
					txtColor(15);
					gotoxy(70, 20);
					cout << "You must create semester first!";
					Sleep(1000);
					gotoxy(70, 20);
					txtColor(0);
					cout << "You must create semester first!";
					txtColor(15);
					continue;
				}
				Nocursortype();
				fillBlackMenu();
				txtColor(15);
				gotoxy(140, 21);	cout << " V I E W ";
				gotoxy(140, 24);	cout << " E D I T ";
				txtColor(240);
				gotoxy(140, 27);	cout << " D E L E T E ";
				txtColor(15);

				deleteCourseMain(COURSE);
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
	gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
	gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";

	while (true) {
		char choice = _getch();
		txtColor(15);
		gotoxy(135, 18);	cout << " I M P O R T   C S V ";
		gotoxy(135, 21);	cout << " E X P O R T   C S V ";
		gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
		gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
		gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";

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
<<<<<<< Updated upstream

			gotoxy(135, 18);	cout << " I M P O R T   C S V ";
=======
			gotoxy(135, 21);	cout << " E X P O R T   C S V ";
>>>>>>> Stashed changes
			if (choice == 13)
			{
				if (Sem == "") {
					txtColor(15);
					gotoxy(70, 20);
					cout << "You must create semester first!";
					Sleep(1000);
					gotoxy(70, 20);
					txtColor(0);
					cout << "You must create semester first!";
					txtColor(15);
					continue;
				}

				Nocursortype();
				fillBlackMenu();
				txtColor(240);
				gotoxy(135, 18);	cout << " I M P O R T   C S V ";
				txtColor(15);
				gotoxy(135, 21);	cout << " E X P O R T   C S V ";
				gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
				gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
				gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";

				txtColor(15);
				UnNocursortype();
				string courseID;
				ifstream f;
				gotoxy(70, 20);
				cout << "Please input course ID: ";
				cin >> courseID;
<<<<<<< Updated upstream

				gotoxy(70, 21);
				cout << "Please input file: ";
				cin >> fileName;

				f.open(fileName);
				int temp = 22;
				if (!f.is_open()) {
					gotoxy(70, temp);
					cout << "Import file failed!";
					Sleep(500);
					Nocursortype();
					fillBlackMenu();
					txtColor(240);
					gotoxy(135, 18);	cout << " I M P O R T   C S V ";
					txtColor(15);
					gotoxy(135, 21);	cout << " E X P O R T   C S V ";
					gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
					gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
					gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
=======
				f.open(Schoolyear + "/Semesters/" + Sem + "/" + courseID + "/Scoreboard.csv");
				int temp = 21;
				while (!f.is_open()) {
					gotoxy(70, temp);
					cout << "Please input course ID: ";
					cin >> courseID;
					f.open(Schoolyear + "/Semester/" + Sem + "/" + courseID + "/Scoreboard.csv");
					temp++;
>>>>>>> Stashed changes
				}
				else {
					importScoreboardCourse(f, courseID);
					importScoreboardStudent(f, courseID);
					f.close();

<<<<<<< Updated upstream
				}
=======
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
>>>>>>> Stashed changes
			}
		}
		
		// Export CSV
		if (dem == 2)
		{
			txtColor(240);
<<<<<<< Updated upstream
			gotoxy(135, 21);	cout << " E X P O R T   C S V ";
=======

			gotoxy(135, 21);	cout << " I M P O R T   C S V ";
>>>>>>> Stashed changes
			if (choice == 13)
			{
				if (Sem == "") {
					txtColor(15);
					gotoxy(70, 20);
					cout << "You must create semester first!";
					Sleep(1000);
					gotoxy(70, 20);
					txtColor(0);
					cout << "You must create semester first!";
					txtColor(15);
					continue;
				}

				Nocursortype();
				fillBlackMenu();
				txtColor(15);
				gotoxy(135, 18);	cout << " I M P O R T   C S V ";
				txtColor(240);
				gotoxy(135, 21);	cout << " E X P O R T   C S V ";
				txtColor(15);
				gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
				gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
				gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";

				txtColor(15);
				UnNocursortype();
				string fileName, courseID;
				ifstream f;

				gotoxy(70, 20);
				cout << "Please enter course ID: ";
				cin >> courseID;
<<<<<<< Updated upstream
				f.open(Schoolyear + "/Semesters/" + Sem + "/" + courseID + "/Scoreboard.csv");
				int temp = 21;
				if (!f.is_open()) {
					gotoxy(70, temp);
					cout << "Export file failed!";
					Sleep(500);
					Nocursortype();
					fillBlackMenu();
					txtColor(15);
					gotoxy(135, 18);	cout << " I M P O R T   C S V ";
					txtColor(240);
					gotoxy(135, 21);	cout << " E X P O R T   C S V ";
					txtColor(15);
					gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
					gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
					gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
				}
				else {
					exportCourseStudent(f);
					f.close();
				}
=======

				gotoxy(70, 21);
				cout << "Please input file: ";
				cin >> fileName;

				f.open(fileName);
				int temp = 22;
				while (!f.is_open()) {
					gotoxy(70, temp);
					cout << "Please enter course ID: ";
					cin >> courseID;
					temp++;
					gotoxy(70, temp);
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
				gotoxy(135, 18);	cout << " E X P O R T   C S V ";
				txtColor(15);
				gotoxy(135, 21);	cout << " I M P O R T   C S V ";
				gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
				gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
				gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
>>>>>>> Stashed changes
			}
		}
		// View Course Scoreboard
		if (dem == 3)
		{
			txtColor(240);
			gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
			if (choice == 13)
			{
				if (Sem == "") {
					txtColor(15);
					gotoxy(70, 20);
					cout << "You must create semester first!";
					Sleep(1000);
					gotoxy(70, 20);
					txtColor(0);
					cout << "You must create semester first!";
					txtColor(15);
					continue;
				}

				Nocursortype();
				fillBlackMenu();
				txtColor(15);
				gotoxy(135, 18);	cout << " I M P O R T   C S V ";
				gotoxy(135, 21);	cout << " E X P O R T   C S V ";
				txtColor(240);
				gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
				txtColor(15);
				gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
				gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";

				txtColor(15);
				string courseID;
				ifstream f;

				gotoxy(70, 20);
				cout << "Please input course ID: ";
				cin >> courseID;

				f.open(Schoolyear + "/Semesters/" + Sem + "/" + courseID + "/Scoreboard.csv");
				int temp = 21;

				if (!f.is_open()) {
					txtColor(15);
					gotoxy(70, temp);
					cout << "Open file failed!";
					Sleep(500);
					Nocursortype();
					fillBlackMenu();
					txtColor(15);
					gotoxy(135, 18);	cout << " I M P O R T   C S V ";
					gotoxy(135, 21);	cout << " E X P O R T   C S V ";
					txtColor(240);
					gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
					txtColor(15);
					gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
					gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
				}
				else {
					viewCourseScoreboard(f);
					f.close();
				}


			}
		}
		// View Class Scoreboard
		// Update Student Score
		if (dem == 4)
		{
			txtColor(240);
			gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
			if (choice == 13)
			{
				if (Sem == "") {
					txtColor(15);
					gotoxy(70, 20);
					cout << "You must create semester first!";
					Sleep(1000);
					gotoxy(70, 20);
					txtColor(0);
					cout << "You must create semester first!";
					txtColor(15);
					continue;
				}

				Nocursortype();
				fillBlackMenu();
				txtColor(15);
				gotoxy(135, 18);	cout << " I M P O R T   C S V ";
				gotoxy(135, 21);	cout << " E X P O R T   C S V ";
				gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
				txtColor(240);
				gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
				txtColor(15);
				gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";

				txtColor(15);
				UnNocursortype();
				string studentID, className, courseID, oldcourseDir, oldstudentDir, newcourseDir, newstudentDir;
				ifstream f1, f2;
				ofstream nf1, nf2;
				Scores newScore;
				int temp = 24;

				gotoxy(70, 20);		cout << "Please input course ID: ";	cin >> courseID;
				gotoxy(70, 21);		cout << "Please input class ID: ";	cin >> className;
				gotoxy(70, 22);		cout << "Please input student ID: ";	cin >> studentID;

				oldcourseDir = "./" + Schoolyear + "/Semesters/" + Sem + "/" + courseID + "/Scoreboard.csv";
				oldstudentDir = "./" + Schoolyear + "/Classes/" + className + "/" + studentID + "/Course " + Sem + " Scoreboard.csv";

				f1.open(oldcourseDir);
				f2.open(oldstudentDir);

				if (!(f1.is_open() && f2.is_open())) {
					gotoxy(70, temp);	cout << "Open file failed!";
					Sleep(500);
					Nocursortype();
					fillBlackMenu();
					txtColor(15);
					gotoxy(135, 18);	cout << " I M P O R T   C S V ";
					gotoxy(135, 21);	cout << " E X P O R T   C S V ";
					gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
					txtColor(240);
					gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
					txtColor(15);
					gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
				}
				else {
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
			

					remove(oldcourseDir.c_str());
					remove(oldstudentDir.c_str());

					rename(newcourseDir.c_str(), oldcourseDir.c_str());
					rename(newstudentDir.c_str(), oldstudentDir.c_str());

				}

				
			}
		}
		if (dem == 5)
		{
			txtColor(240);
			gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";
			if (choice == 13)
			{
				if (Sem == "") {
					txtColor(15);
					gotoxy(70, 20);
					cout << "You must create semester first!";
					Sleep(1000);
					gotoxy(70, 20);
					txtColor(0);
					cout << "You must create semester first!";
					txtColor(15);
					continue;
				}

				Nocursortype();
				fillBlackMenu();
				txtColor(15);
				gotoxy(135, 18);	cout << " I M P O R T   C S V ";
				gotoxy(135, 21);	cout << " E X P O R T   C S V ";
				gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
				gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
				txtColor(240);
				gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";

				txtColor(15);
				UnNocursortype();
				string className;
				ifstream f;
				int temp = 21;

				gotoxy(70, 20);
				cout << "Please input class name: ";
				cin >> className;
				f.open(Schoolyear + "/Classes/" + className + "/allStudents.csv");

				if (!f.is_open()) {
					gotoxy(70, temp);
					cout << "Class not found!";
					Sleep(500);
					Nocursortype();
					fillBlackMenu();
					txtColor(15);
					gotoxy(135, 18);	cout << " I M P O R T   C S V ";
					gotoxy(135, 21);	cout << " E X P O R T   C S V ";
					gotoxy(122, 24);	cout << " V I E W   C O U R S E   S C O R E B O A R D ";
					gotoxy(123, 27);	cout << " U P D A T E   S T U D E N T   R E S U L T ";
					txtColor(240);
					gotoxy(121, 30);	cout << " V I E W   C L A S S   S C O R E B O A R D ";

					txtColor(15);
				}
				else {
					viewClassScoreboard(f, className);
					f.close();
				}

				viewClassScoreboard(f, className);
				f.close();
			}
		}
	}
}