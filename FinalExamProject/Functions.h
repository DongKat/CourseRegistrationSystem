#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__


#include "Struct.h"
#include "UI.h"

void readClassCSV(ifstream& classList, Students& student);

void createStudent(ifstream& classList, Students& student);

void createStudentList(Students*& pHead, string csvFileName);

void exportCourseStudent(ifstream& f);

void viewCourseScoreboard(ifstream& f);

void viewStudentScoreboard(ifstream& f);

string checkStudentInClass(string studentID);

void importScoreboard(Courses* courseHead, string courseID);

void deleteMarks(CourseScore*& pHead);

void updateStudentResult(Courses Course, string studentID, Scores newScore);

void viewClassScoreboard(Classes Class);

time_t timeToUnixTime(date end);

bool isCourseRegistrationSessionActive(date registerStartDay, date registerEndDay);

#endif // !_FUNCTIONS_H_