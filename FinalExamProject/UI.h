#pragma once

#include "Library.h"
#include "Struct.h"

void Nocursortype();
void UnNocursortype();
void gotoxy(int x, int y);
void txtColor(int color);
void setWindowFullSize();
void logo_moodle();
void loginUI();
void fillBlackLogin();

string convertToString(char* a, int size);
string inputUsername(char username[], int& sizeUser);
string inputPassword(char password[], int& sizePass);
bool checkValidUsernameAndPasswordStaff(string username, string password);
bool checkValidUsernameAndPasswordStudent(string username, string password);
void menuStaffSettings(char username[], char password[], int sizeUser, int sizePass);
