#ifndef __UI_H_INCLUDED__ 
#define __UI_H_INCLUDED__ 


#include "Struct.h"

void Nocursortype();
void UnNocursortype();
void gotoxy(int x, int y);
void txtColor(int color);
void setWindowFullSize();
void logo_moodle();
void loginUI();
void fillBlackLogin();
void fillBlackUserPass();
void fillBlackMenu();

string convertToString(char* a, int size);
string inputUsername(char username[], int& sizeUser);
string inputPassword(char password[], int& sizePass);
bool checkValidUsernameAndPasswordStaff(string username, string password);
bool checkValidUsernameAndPasswordStudent(string username, string password);
void Login(char username[], char password[], int sizeUser, int sizePass);
void menuStaff(char username[], char password[], int sizeUser, int sizePass);
void menuStaffSettings(char username[], char password[], int sizeUser, int sizePass);
void menuStudent(char username[], char password[], int sizeUser, int sizePass);
void menuStudentSettings(char username[], char password[], int sizeUser, int sizePass);

#endif // !_UI_H_