#pragma once
#include "Library.h"
#include "Struct.h"
#include "UI.h"
#include "Functions.h"

bool createFolder(string path);

void removeFolder(string path);

void removeFile(string path);

bool checkDate(date Date1, date Date2);

bool createFolderSchoolYear(string path);

bool inputSchoolYear();

date convertToDay(string Day);

void printDateToFile(date Date, ofstream& f);

void printDateToConsole(date Date);

void createFolderStudent(string path);

Students* newStudent(int no, string ID, string FirstName, string LastName, string gender, date dateOfBirth, string idSocial, string className, string folder);

Classes* newClass(string filepath, string className, string folder);

void createFolderClass(string path, string Cname);

void addClass(Classes*& Class, string folder);

Semesters newSemester(int currSem, date begin, date end);

void addSemester(Semesters* semester, int currSem, date begin, date end);

bool loadYearAndSem();

void addNewSemesterMain(Semesters* semester);

Courses* newCourse(string courseName, string courseID, string teacherName, int numCredits, int maxStudent, Schedules schedule[]);

Courses* addCourse(Courses*& course, string courseName, string courseID, string teacherName, int numCredits, int maxStudent, Schedules* schedule);

void createFolderNFileCourse(Courses* course);

void viewCourseFile(Courses* course);

Courses* findCourse(Courses*& course, string courseID, string courseName, string teacherName);

void deleteCourse(Courses*& course, Courses* delCourse);

void addNewCourseMain(Courses*& course);

void deleteCourseMain(Courses*& course);

void deleteCourseFolder(Courses* delCourse);

void editCourseMain(Courses*& course);

bool loadCoursesFromFile(Courses*& course);
