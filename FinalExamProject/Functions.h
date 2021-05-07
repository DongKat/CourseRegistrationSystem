#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "Struct.h"
#include "UI.h"

#endif // !_FUNCTIONS_H_
bool isLegalDate(date someday);

void deleteMarks(CourseScore*& pHead);

string checkStudentClass(string studentID);

//void importScoreboard(Courses* courseHead, string courseID, Students& student, string scoreboard_file_name);

void importScoreboardCourse(ifstream& f, string courseID);

void importScoreboardStudent(ifstream& f, string courseID);

void exportCourseStudent(ifstream& file);

void viewCourseScoreboard(ifstream& f);

void viewOwnScoreboard(ifstream& f, int pos);

float getSemGPA(ifstream& f);

void updateStudentResult(ifstream& f1, ifstream& f2, ofstream& nf1, ofstream& nf2, string studentID, string courseID, Scores newScore);

void viewClassScoreboard(ifstream& f, string className);
