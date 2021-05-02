#ifndef __MENUSTUDENT_H_INCLUDED__
#define __MENUSTUDENT_H_INCLUDED__

#include "Struct.h"
#include "Functions.h"
#include "UI.h"
#include "InputLogin.h"
#include "EnrollCourse.h"

void MenuStudent(char username[], char password[], int sizeUser, int sizePass);
void MenuStudentSettings(char username[], char password[], int sizeUser, int sizePass);
void MenuStudentProfileInfo(string username, string password);
void MenuChangePasswordStudent(string username, string &password);

#endif
