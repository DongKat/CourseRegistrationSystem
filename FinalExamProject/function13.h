#pragma once
#include "Struct.h"
string Schoolyear;


void enrollACourse(Students& aStudent, Courses courseNew, fstream& f);

void updateCourse(Students aStudent, Courses courseDelete, fstream& f);

void removeACourse(Students aStudent, Courses courseDelete, fstream& f);
