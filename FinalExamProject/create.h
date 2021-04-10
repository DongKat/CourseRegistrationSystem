#pragma once

#include "Library.h"
#include "Struct.h"

using namespace std;

void createSchoolYear(schoolYear*& sYear, int yearStart, int yearEnd);
date convertToDay(string Day);
Students* newStudent(int no, int ID, string FirstName, string LastName, bool gender, date dateOfBirth, string idSocial);
Classes* newClass(string filepath, string className);
schoolYear* newSchoolYear(int yearStart, int yearEnd);
void addClass(schoolYear*& sYear);
void deleteStudent(Students*& stu);
void deleteClass(Classes*& Class);
void deleteYear(schoolYear*& sYear);
