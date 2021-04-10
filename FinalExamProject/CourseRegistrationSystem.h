#ifndef __COURSEREGISTRATIONSYSTEM_H_
#define __COURSEREGISTRATIONSYSTEM_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <direct.h> // mkdir

using namespace std;

void autoGenerateStaffAccounts(string filePath);
void autoGenerateStudentAccounts(string filePath);
void autoGenerateStaffProfiles(string filePath);
void autoGenerateStudentProfiles(string filePath);


#endif
