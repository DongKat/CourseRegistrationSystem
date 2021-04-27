#include "AutoGenerate.h"
#include "create.h"
#include "Functions.h"
#include "InputLogin.h"
#include "loadClass_Students.h"
#include "Library.h"
#include "MenuStaff.h"
#include "MenuStudent.h"
#include "Struct.h"
#include "UI.h"

string Schoolyear =" ";
date dateStart;
date dateEnd;
string Sem = " ";
Semesters SEMESTER[3];
Courses* COURSE;
Classes* CLASS;

int main() {
	setWindowFullSize();
	txtColor(0);
	/*autoGenerateStudentAccounts("student.csv");*/
	autoGenerateStudentProfiles("student1.csv");
	autoGenerateStaffProfiles("staff.txt");

	char username[23];
	char password[23];
	int sizeUser = 0;
	int sizePass = 0;

	Login(username, password, sizeUser, sizePass);

	return 0;
}
