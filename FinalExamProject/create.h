#pragma once
#include "Struct.h"
#include "UI.h"
#include "AutoGenerate.h"
#include "Functions.h"

date convertToDay(string Day);

bool checkDate(date Date1, date Date2);

Courses* findCourse(Courses*& course, string courseID, string courseName, string teacherName);

bool loadCoursesFromFile(Courses*& course);

bool loadYearAndSem();

void viewCourseFile(Courses* course);

bool createFolder(string path);

void removeFolder(string path);

void removeFile(string path);

void printDateToFile(date Date, ofstream& f);

void printDateToConsole(date Date);

void createFolderStudent(string path);

Students* newStudent(int no, string ID, string FirstName, string LastName, string gender, date dateOfBirth, string idSocial, string className, string folder);

bool inputSchoolYear();

bool createFolderSchoolYear(string path);

Classes* newClass(string filepath, string className, string folder);

void createFolderClass(string path, string Cname);

void addClass(Classes*& Class, string folder);

Semesters newSemester(int currSem, date begin, date end);

void addSemester(Semesters* semester, int currSem, date begin, date end);

Courses* newCourse(string courseName, string courseID, string teacherName, int numCredits, int maxStudent, Schedules schedule[]);

Courses* addCourse(Courses*& course, string courseName, string courseID, string teacherName, int numCredits, int maxStudent, Schedules* schedule);

void createFolderNFileCourse(Courses* course);

void deleteCourse(Courses*& course, Courses* delCourse);

void deleteCourseFolder(Courses* delCourse);

void addNewCourseMain(Courses*& course);

void addNewSemesterMain(Semesters* semester);

void editCourseMain(Courses*& course);

void deleteCourseMain(Courses*& course);
