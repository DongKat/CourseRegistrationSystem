#include "loadClass_Students.h"
#include "create.h";

BasicCourses *loadCourse(string path){
    BasicCourses *course=0,*tmp=0;
    ifstream f;
    f.open(path);
    while (!f.eof()){
        if (course){
            tmp->next=new BasicCourses;
            tmp=tmp->next;
        }
        else {
            course=new BasicCourses;
            tmp=course;
        }
        getline(f,tmp->courseID,',');
        getline(f,tmp->courseName,',');
        f>>tmp->mark->Midterm >> tmp->mark->Final >> tmp->mark->Bonus >> tmp->mark->GPA;
        f.ignore(100000,',');
        getline(f,tmp->schedule[0].day,',');
        getline(f,tmp->schedule[0].time,',');
        getline(f,tmp->schedule[1].day,',');
        getline(f,tmp->schedule[1].time);
    }    
    f.close();
    return course;
}

Students *loadStudentInfo(string path){         //path: schoolyear/classes/classname/id/
    Students *stu=0;
    ifstream f;
    f.open(path+"Profile.txt");                 // get student's basic info
    f >> stu->no;
    getline(f,stu->ID);
    getline(f,stu->firstName);
    getline(f,stu->lastName);
    getline(f,stu->gender);
    string DOB;
    getline(f,DOB);
    stu->dateOfBirth=convertToDay(DOB);
    getline(f,stu->idSocial);



    return stu;
}

Students *loadStudent(string path, string ClassName){ // path: schoolyear/Classes/ClassName/
    Students *stu=0;
    ifstream f;
    f.open(path+ClassName+".txt");
    if (!f.is_open()) return 0;
    while (!f.eof()){
        string ID;
        getline(f,ID);
        string StudentPath=path+"\\"+ID;

    }
    f.close();
    return stu;
}

Classes* loadClass(){
    Classes* Class=0;
    string path=Schoolyear+"\\Classes\\";
    string listClass=path+"Classes.txt";
    ifstream f;
    f.open(listClass);
    if (!f.is_open()) return 0;
    Classes *tmp=0;
    while (!f.eof()){
        string ClassName;
        getline(f,ClassName);
        if (Class){
           tmp->next=new Classes;
           tmp=tmp->next;
        }
        else{
            Class=new Classes;
            tmp=Class;
        }
        tmp->className=ClassName;
        tmp->next=0;
        tmp->prev=0;
        tmp->next->prev=tmp;
        tmp->student=loadStudent(path+ClassName+"\\",ClassName);
    }
    return Class;
}