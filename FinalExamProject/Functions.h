#pragma once

#include "Library.h"
#include "Struct.h"


void readClassCSV(ifstream& classList, Students& student);


void createStudent(ifstream& classList, Students& student);

void createStudentList(Students*& pHead, string csvFileName);

void exportCourseStudent(Courses Course);

void viewScoreboard(Courses Course);

void importScoreboard(Courses Course);

void updateStudentResult(Courses Course, string studentID);

void viewClassScoreboard(Courses Course, string className);
