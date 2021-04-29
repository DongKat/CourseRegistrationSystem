#pragma once

#include "Struct.h"

time_t timeToUnixTime(date end);
bool isCourseRegistrationSessionActive(date registerStartDay, date registerEndDay);
bool checkSchedule(Students aStudent, Courses courseNew);
void enrollACourse(Students& aStudent, Courses& courseNew, fstream& f);
void viewEnrolledCourses(Students aStudent, fstream& f);
void updateCourseB4D(Students& aStudent, Courses& courseDelete, fstream& f);
void removeACourse(Students* aStudent, Courses* courseDelete, fstream& f);
void viewAllStudentInCourse(Courses* course);
void viewAllStudentInClass(Classes* Class);
