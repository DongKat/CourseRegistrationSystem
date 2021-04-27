#include "Struct.h"

void deleteCouseScore(CourseScore *&head)
{
    while (head) {
        CourseScore *tmp=head;
        head=head->next;
        delete tmp;
    }
}

void deleteCourse()
{
    Courses *pCourse=COURSE;
    Courses *pdeleteCourse;
    while (pCourse!=nullptr)
    {
        BasicStudents *pStu=COURSE->studentID;
        BasicStudents *pdeleteStu;
        while (pStu!=nullptr)
        {
            pdeleteStu=pStu;
            pStu=pStu->next;
            delete pdeleteStu;
        }

        deleteCouseScore(COURSE->mark);
        
        pdeleteCourse=pCourse;
        pCourse=pCourse->next;
        delete pdeleteCourse;
    }
};

void deleteCourse()
{
    Classes *pClass=CLASS;
    Classes *pdeleteClass;
    while (pClass!=nullptr)
    {
        deleteCouseScore(CLASS->student->courseStudent->mark);
        
        BasicCourses *pStu=CLASS->student->courseStudent;
        BasicCourses *pdeleteStu;
        while (pStu!=nullptr)
        {
            pdeleteStu=pStu;
            pStu=pStu->next;
            delete pdeleteStu;
        }
        
        Students *pStudent=CLASS->student;
        Students *pdeleteStudent;
        while (pStudent!=nullptr)
        {
            pdeleteStudent=pStudent;
            pStudent=pStudent->next;
            delete pdeleteStudent;
        }
        
        pdeleteClass=pClass;
        pClass=pClass->next;
        delete pdeleteClass;
    }
}
