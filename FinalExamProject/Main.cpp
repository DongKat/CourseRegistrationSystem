#include "CourseRegistrationSystem.h"
#include "create.h"
#include "Functions.h"
#include "UI.h"
#include "Struct.h"
#include "Library.h"

string Schoolyear;
date dateStart;
date dateEnd;
string Sem;

int main() {
	setWindowFullSize();
	txtColor(0);
	autoGenerateStudentAccounts("student.csv");
	autoGenerateStaffAccounts("staff.txt");
	autoGenerateStudentProfiles("student.csv");
	autoGenerateStaffProfiles("staff.txt");

	char username[23];
	char password[23];
	int sizeUser = 0;
	int sizePass = 0;

	Login(username, password, sizeUser, sizePass);

	system("cls");
	logo_moodle();
	txtColor(15);

	return 0;
}
