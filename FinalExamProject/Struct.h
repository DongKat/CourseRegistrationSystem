<<<<<<< Updated upstream
=======
﻿#ifndef function_h
#define function_h

>>>>>>> Stashed changes
#pragma once
#include "Library.h"

using namespace std;

string Schoolyear;

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
    int countStudent;
    BasicStudents *studentID;//8 [50] là tối đa 50 SV 1 lớp - 13 ghi danh- 15 xoá khoá- 16 xem các môn mà sv học
    Schedules schedule[2];
    Scores scoreBoard;// 22-26
    CourseScore *mark;
    Courses *prev, *next;
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
    Courses courseStudent[15];
    // 13 [15] mỗi sem tối đa 5 course x3 sem, dùng tra cứu, kiểm tra thời gian buổi học - 14 xem danh sách các khoá đã ghi danh - 15 xoá khoá - 20-26
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