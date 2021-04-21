#ifndef __INPUTLOGIN_H_INCLUDED__ 
#define __INPUTLOGIN_H_INCLUDED__ 

#include "Struct.h"

string inputUsername(char username[], int& sizeUser);
string inputPassword(char password[], int& sizePass);
bool checkValidUsernameAndPasswordStaff(string username, string password);
bool checkValidUsernameAndPasswordStudent(string username, string password);
void Login(char username[], char password[], int sizeUser, int sizePass);

#endif