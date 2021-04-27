#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__


#include "Struct.h"
#include "UI.h"


#endif // !_FUNCTIONS_H_
bool isLegalDate(date someday);

void readClassCSV(ifstream& classList, Students& student);

void createStudent(ifstream& classList, Students& student);

void createStudentList(Students*& pHead, string csvFileName);

void deleteMarks(CourseScore*& pHead);

string checkStudentInClass(string studentID);

//void importScoreboard(Courses* courseHead, string courseID, Students& student, string scoreboard_file_name);

void importScoreboardCourse(ifstream& f, string courseID);

void importScoreboardStudent(ifstream& f, string courseID);

void exportCourseStudent(ifstream& file);

void viewCourseScoreboard(ifstream& f);


void updateStudentResult(ifstream& f1, ifstream& f2, ofstream& nf1, ofstream& nf2, string studentID, string courseID, Scores newScore);

