#ifndef _CREATE_H_
#define _CREATE_H_

#include "Library.h"
#include "Struct.h"
#include <direct.h>

using namespace std;

void createFolder(string path);
void removeFolder(string path);
bool checkDate(date Date1, date Date2);
void addSchoolYear(schoolYear*& sYear, int yearStart, int yearEnd);
date convertToDay(string Day);
void printDateToFile(date Date, ofstream &f);
void printDateToConsole(date Date);
Students* newStudent(int no, string ID, string FirstName, string LastName, string gender, date dateOfBirth, string idSocial, string className, string folder);
Classes* newClass(string filepath, string className, string folder);
schoolYear* newSchoolYear(int yearStart, int yearEnd);
void addClass(schoolYear*& sYear, string folder);
void deleteAllStudents(Students*& stu, string path);
void deleteStudent(Students *&stu, string path);
void deleteAllClasses(Classes*& Class, string path);
void deleteClass(Classes *&Class, string path);
void deleteAllYears(schoolYear*& sYear);
void deleteYear(schoolYear*& sYear);

#endif