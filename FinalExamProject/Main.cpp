#include "CourseRegistrationSystem.h"
#include "create.h"
#include "Functions.h"
#include "UI.h"
#include "Library.h"
#include "Struct.h"

int main() 
{
	setWindowFullSize();
	logo_moodle();
	loginUI();

	autoGenerateStudentAccounts("student.csv");
	autoGenerateStaffAccounts("staff.csv");
	autoGenerateStudentProfiles("student.csv");
	autoGenerateStaffProfiles("staff.csv");

	char username[23];
	char password[23];
	int sizeUser = 0;
	int sizePass = 0;

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

	system("cls");
	logo_moodle();
	txtColor(15);

	return 0;
}
