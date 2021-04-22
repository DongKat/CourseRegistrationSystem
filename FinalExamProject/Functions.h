#ifndef __FUNCTIONS_H_INCLUDED__ 
#define __FUNCTIONS_H_INCLUDED__ 


#include "Struct.h"

void readClassCSV(ifstream& classList, Students& student);

void createStudent(ifstream& classList, Students& student);

void createStudentList(Students*& pHead, string csvFileName);

void exportCourseStudent(Courses course);

void viewCourseScoreboard(Courses course);

void viewStudentScoreboard(Students student);

string checkStudentInClass(string studentID);

void importScoreboard(Courses* courseHead, string courseID);

void deleteMarks(CourseScore*& pHead);

void updateStudentResult(Courses Course, string studentID, Scores newScore);

void viewClassScoreboard(Classes Class);

time_t timeToUnixTime(date end);

bool isCourseRegistrationSessionActive(date registerStartDay, date registerEndDay);

#endif // !_FUNCTIONS_H_