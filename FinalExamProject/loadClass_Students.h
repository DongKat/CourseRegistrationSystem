#ifndef _LOADCLASS_STUDENTS_H_
#define _LOADCLASS_STUDENTS_H_

#include "create.h"

float convertToFloat(string score);
BasicCourses* loadCourse(string path);
Students* loadStudentInfo(string path);
Students* loadStudent(string path, string ClassName);
void loadClassFromFile(Classes*& pClass);

#endif
