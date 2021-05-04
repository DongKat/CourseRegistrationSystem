#pragma once
#include "Library.h"

using namespace std;

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
	string time; // 8 Lưu ca S1, S2,....
};
struct Scores
{
	float Total;
	float Midterm;
	float Final;
	float Bonus;
};

struct CourseScore : Scores
{
	string studentID;
	CourseScore* next = nullptr;
};

struct BasicStudents
{
	int No;
	string ID;
	string firstName;
	string lastName;
	string className;
	BasicStudents* next = nullptr;
	BasicStudents* prev = nullptr;
};

struct BasicCourses
{
	int sem;
	string courseID;
	string courseName;
	Schedules schedule[2];
	BasicCourses* next = nullptr;
};

struct Courses
{
	int sem;
	string courseName;
	string courseID;
	string teacherName;
	int numCredits;
	int maxStudent;// cap phat studentID
	int countStudent = 0;
	BasicStudents* studentID = nullptr;//8 [50] là tối đa 50 SV 1 lớp - 13 ghi danh- 15 xoá khoá- 16 xem các môn mà sv học

	//CourseScore* mark;

	Schedules schedule[2];
	Courses* prev = nullptr, * next = nullptr;
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

	BasicCourses* courseStudent = nullptr;

	Students* next = nullptr;
	Students* prev = nullptr;
};

struct Semesters
{
	int sem;

	Courses* course; // 7-11, 19 xem các môn có trong kỳ ( dù có học hay không học )
	Semesters* next = nullptr, * prev = nullptr;
};

struct Classes
{
	string className;
	Students* student; // 3 thêm sinh viên vào lớp , 18 xem danh sách sinh viên 1 lớp
	Classes* next = nullptr;
	Classes* prev = nullptr;
};

struct schoolYear // 1 tạo năm học
{
	int yearStart;
	int yearEnd;
	Classes* Class; //2 tạo lớp - 17 xem danh sách lớp
	Semesters Sem[3];
	schoolYear* next;
	schoolYear* prev;
};

extern string Schoolyear;
extern date dateStart;
extern date dateEnd;
extern string Sem;
extern Semesters SEMESTER[3];
extern Courses* COURSE;
extern Classes* CLASS;
