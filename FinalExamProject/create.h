#pragma once

#include "Library.h"
#include "Struct.h"

using namespace std;

void creatSchoolYear(schoolYear& sYear);
date convertToDay(string Day);
Students* newStudent(int no, int ID, string FirstName, string LastName, bool gender, date dateOfBirth, string idSocial);
Classes* newClass(string filepath, string className);
void addClass(schoolYear& sYear);
void deleteStudent(Students*& stu);
void deleteClass(Classes*& Class);

