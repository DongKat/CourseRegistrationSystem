
#pragma once
#include "Library.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <algorithm>
using namespace std;
string Schoolyear = "";

struct date
{
    int day;
    int month;
    int year;
};

struct StaffAccount
{
    string username;
    string name;
    string password;
    string gender;
    date dateOfBirth;
    string idSocial;
    string phoneNumber;
};

struct Schedules
{
    string day; // 8 lưu thứ MON, SAT,..
    string time; // 8 Lưu ca S1, S2,..
};
struct Scores
{
    float GPA;
    float Midterm;
    float Final;
    float Bonus;
};

struct CourseScore : Scores
{
    string studentID;
};

struct BasicStudents
{
    string ID;
    string firstName;
    string lastName;
    BasicStudents *next = nullptr;
    BasicStudents *prev;
};
struct BasicCourses
{
    int sem;
    string courseName;
    string courseID;
    CourseScore *mark;
    BasicCourses *next=nullptr;
    Schedules schedule[2];

};

struct Courses
{
    int sem;
    date dateStart; // 7 ngày bắt đầu đăng ký môn
    date dateEnd;  // 7 ngày kết thúc đăng ký môn
    string courseName;
    string courseID;
    string teacher_name;
    int numCredits;
    int maxStudent;// cap phat studentID
    int countStudent=0;
    BasicStudents *studentID;//8 [50] là tối đa 50 SV 1 lớp - 13 ghi danh- 15 xoá khoá- 16 xem các môn mà sv học
    CourseScore *mark;
    Schedules schedule[2];
    Scores scoreBoard;// 22-26
    Courses *next=nullptr , *prev;
};

struct Students
{
    int no;
    string className;
    string ID;
    string password;
    string firstName;
    string lastName;
    string gender;
    date dateOfBirth;
    string idSocial;
    BasicCourses *courseStudent=nullptr;
    Students *next;
    Students *prev;
};

struct Semesters
{
    int sem;
    date dateStart;// 6 ngày bắt đầu học kỳ
    date dateEnd;// 6 ngày kết thúc học kỳ
    Courses *course; // 7-11, 19 xem các môn có trong kỳ ( dù có học hay không học )
};

struct Classes
{
    string className;
    Students *student; // 3 thêm sinh viên vào lớp , 18 xem danh sách sinh viên 1 lớp
    Classes *next;
    Classes *prev;
};

struct schoolYear // 1 tạo năm học
{
    int yearStart;
    int yearEnd;
    Classes *Class; //2 tạo lớp - 17 xem danh sách lớp
    Semesters Sem[3];
    schoolYear *next;
    schoolYear *prev;
};
