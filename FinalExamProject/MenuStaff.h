#ifndef __MENUSTAFF_H_INCLUDED__ 
#define __MENUSTAFF_H_INCLUDED__ 

#include "Struct.h"
#include "Functions.h"
#include "UI.h"
#include "create.h"
#include "InputLogin.h"

void MenuStaff(char username[], char password[], int sizeUser, int sizePass);
void MenuStaffSettings(char username[], char password[], int sizeUser, int sizePass);
void MenuStaffProfileInfo(string username, string password);
void MenuChangePasswordStaff(string username, string& password);
void MenuEditCourses(char username[], char password[], int sizeUser, int sizePass);
void MenuStaffScoreboard(char username[], char password[], int sizeUser, int sizePass);
void MenuCreateNew(char username[], char password[], int sizeUser, int sizePass);

#endif