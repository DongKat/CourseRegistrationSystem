#include "Struct.h"
#include "deleteFinal.h"

void deleteCouseScore(CourseScore*& head)
{
	while (head) {
		CourseScore* tmp = head;
		head = head->next;
		delete tmp;
	}
}

void deleteCourses()
{
	Courses* pCourse = COURSE;
	Courses* pdeleteCourse;
	while (pCourse != nullptr)
	{
		BasicStudents* pStu = pCourse->studentID;
		BasicStudents* pdeleteStu;
		while (pStu != nullptr)
		{
			pdeleteStu = pStu;
			pStu = pStu->next;
			delete pdeleteStu;
		}

		//deleteCouseScore(COURSE->mark);

		pdeleteCourse = pCourse;
		pCourse = pCourse->next;
		delete pdeleteCourse;
	}
};

void deleteClasses()
{
	Classes* pClass = CLASS;
	Classes* pdeleteClass;
	while (pClass != nullptr)
	{
		//deleteCouseScore(CLASS->student->courseStudent->mark);
		Students* pStudent = pClass->student;
		Students* pdeleteStudent;
		while (pStudent != nullptr)
		{
			BasicCourses* pStu = pStudent->courseStudent;
			BasicCourses* pdeleteStu;
			while (pStu != nullptr)
			{
				pdeleteStu = pStu;
				pStu = pStu->next;
				delete pdeleteStu;
			}
			pdeleteStudent = pStudent;
			pStudent = pStudent->next;
			delete pdeleteStudent;
		}
		pdeleteClass = pClass;
		pClass = pClass->next;
		delete pdeleteClass;
	}
}