#pragma once

#include "UI.h"
#include "Struct.h"

time_t timeToUnixTime(date end);

bool isCourseRegistrationSessionActive(date registerStartDay, date registerEndDay);

bool checkSchedule(Students aStudent, Courses courseNew);

void enrollACourse(Students& aStudent, Courses& courseNew);

void viewEnrolledCourses(Students* aStudent);

void removeACourse(Students* aStudent, Courses* courseDelete);

void updateCourseB4D(Students* aStudent, Courses* courseDelete);

void viewAllStudentInCourse(Courses* course);

void viewAllStudentInClass(Classes* Class);

void viewAllCourse();

void viewAllClass();
