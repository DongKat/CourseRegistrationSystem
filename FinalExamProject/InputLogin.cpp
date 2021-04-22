#include "InputLogin.h"
#include "UI.h"

string convertToString(char* a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

string inputUsername(char username[], int &sizeUser) {
	UnNocursortype();
	sizeUser = 0;
	string user;
	gotoxy(75, 30);
	char x;

	while (true) {
		x = _getch();
		if (sizeUser == 23) {
			while (true) {
				x = _getch();
				if (x == 8 || x == 13)
					break;
			}
		}
		if (x == 13) {
			break;
		}
		if (x == 8) {
			if (sizeUser != 0) {
				username[sizeUser] = '\0';
				sizeUser--;
				cout << "\b \b";
			}
		}
		else {
			cout << x;
			username[sizeUser] = x;
			sizeUser++;
		}
	}
	username[sizeUser] = '\0';
	user = convertToString(username, sizeUser);

	return user;
}

string inputPassword(char password[], int& sizePass) {
	UnNocursortype();
	sizePass = 0;
	string pass;
	gotoxy(75, 35);
	char x;
	//enter = 13	;	backspace = 8
	while (true) {
		x = _getch();
		if (sizePass == 23) {
			while (true) {
				x = _getch();
				if (x == 8 || x == 13)
					break;
			}
		}
		if (x == 13) {
			break;
		}
		if (x == 8) {
			if (sizePass != 0) {
				password[sizePass] = '\0';
				sizePass--;
				cout << "\b \b";
			}
		}
		else {
			cout << x;
			password[sizePass] = x;
			sizePass++;
			cout << "\b \b*";
		}
	}
	password[sizePass] = '\0';
	pass = convertToString(password, sizePass);

	return pass;
}

bool checkValidUsernameAndPasswordStaff(string username, string password) {

	ifstream in;

	in.open("Staff Accounts/" + username);
	if (!in.is_open()) {
		return false;
	}
	else {
		while (!in.eof()) {
			string passwordFile;
			string ignore_line;
			
			getline(in, ignore_line, '\n');
			getline(in, passwordFile, '\n');

			if (password.compare(passwordFile) == 0)
				return true;
			else
				return false;
		}
	}
	in.close();

	return true;
}

bool checkValidUsernameAndPasswordStudent(string username, string password) {

	ifstream in;

	in.open("Student Accounts/" + username);
	if (!in.is_open()) {
		return false;
	}
	else {
		while (!in.eof()) {
			string passwordFile;
			string ignore_line;

			getline(in, ignore_line, '\n');
			getline(in, passwordFile, '\n');
		
			if (password.compare(passwordFile) == 0)
				return true;
			else
				return false;
		}
	}
	in.close();

	return true;
}
