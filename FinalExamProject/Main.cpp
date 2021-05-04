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

string Schoolyear = "";
date dateStart;
date dateEnd;
string Sem = "";
Semesters SEMESTER[3];
Courses* COURSE = nullptr;
Classes* CLASS = nullptr;

int main() {
	setWindowFullSize();
	txtColor(0);

	autoGenerateStaffProfiles("staff.txt");

	try
	{
		loadYearAndSem();
		loadCoursesFromFile(COURSE);
		loadClassFromFile(CLASS);
	}
	catch (const std::exception& ex)
	{
		txtColor(15);
		cout << ex.what();
		_getch();
	}

	//loadYearAndSem();
	//loadCoursesFromFile(COURSE);

	char username[23];
	char password[23];
	int sizeUser = 0;
	int sizePass = 0;

	Login(username, password, sizeUser, sizePass);

	return 0;
}