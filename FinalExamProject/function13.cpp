#include "function.h"
bool checkSchedule(Students aStudent,Courses courseNew)
{
    int i = 0;
    switch (courseNew.sem)
    {
        case 1:
             i=0;
            break;
        case 2:
             i=5;
            break;
        case 3:
             i=10;
            break;
        default:
            break;
    }
    for ( ;i<i+5;i++)
    {
        for (int j =0 ; j < 2; j++)
        if((aStudent.courseStudent[i].schedule[j]->day==courseNew.schedule[j]->day)
           && (aStudent.courseStudent[i].schedule[j]->time==courseNew.schedule[j]->time))
                return false;
    }
    return true;
};

void enrollACourse(Students aStudent,Courses courseNew,fstream &f)
{
    int k=courseNew.sem;
    int count=0;
    f.open(Schoolyear + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(k) + ".csv", ios::app || ios::in || ios::out);
    string ignore_line;
    if(!f.is_open())
        throw "error";
    while(!f.eof())
    {
        getline(f, ignore_line);
        count++;
    }
    
    if((checkSchedule(aStudent,courseNew)==true) && courseNew.countStudent<courseNew.maxStudent)
        if(count<5)
        {
            f << courseNew.courseID << "," << courseNew.courseName << ",0,0,0,0" << endl;
            f.close();
            f.open(Schoolyear + "/Semester/Semester" + to_string(k) + "/" + courseNew.courseID + "Scoreboard.csv", ios::app || ios::in || ios::out);
            int count1 = 0;
            if(!f.is_open())
                throw "error";
            while(!f.eof())
            {
                getline(f, ignore_line);
                count1++;
            }
            f << ++count1 << "," << aStudent.ID << "," << aStudent.firstName << "," << aStudent.lastName << ",0,0,0,0" << endl;
            f.close();
            
            courseNew.countStudent++;
            aStudent.courseStudent[(k-1)*5+count] = courseNew;
            courseNew.studentID->next = new BasicStudents;
            courseNew.studentID->next->firstName = aStudent.firstName;
            courseNew.studentID->next->lastName = aStudent.lastName;
            courseNew.studentID->next->ID = aStudent.ID;
        }
}
void viewEnrolledCourses(Students aStudent, fstream &f)
{
    string courseID;
    string courseName;
    string midscore;
    string finalscore;
    string bonus;
    string overall;
    // in course sem 1
    cout<<"Courses semester 1: "<<endl;
    f.open(to_string(Schoolyear) + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(1) + ".csv");
    if(!f.is_open())
        throw "error";
    while(!f.eof())
    {
        getline(f,courseID,',');
        cout << "Course ID: " << courseID << " " ;
        getline(f,courseName , ',');
        cout << "Course Name: " << courseName << " " ;
        getline(f,midscore , ',');
        cout << "Midterm Score: " <<midscore << " " ;
        getline(f,finalscore, ',');
        cout << "Final Score: " << finalscore << " " ;
        getline(f,bonus , ',');
        cout << "Bonus: " << bonus << " " ;
        getline(f,overall);
        cout << "GPA: " << overall << " " ;
        cout<<endl;
    }
    f.close();

    // in course sem 2
    cout<<"Courses semester 2: "<<endl;
    f.open(to_string(Schoolyear) + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(2) + ".csv");
    if(!f.is_open())
        throw "error";
    while(!f.eof())
    {
        getline(f,courseID,',');
        cout << "Course ID: " << courseID << " " ;
        getline(f,courseName , ',');
        cout << "Course Name: " << courseName << " " ;
        getline(f,midscore , ',');
        cout << "Midterm Score: " <<midscore << " " ;
        getline(f,finalscore, ',');
        cout << "Final Score: " << finalscore << " " ;
        getline(f,bonus , ',');
        cout << "Bonus: " << bonus << " " ;
        getline(f,overall );
        cout << "GPA: " << overall << " " ;
        cout<<endl;
    }
    f.close();
    
    // in course sem 3
    cout<<"Courses semester 3: "<<endl;
    f.open(to_string(Schoolyear)+ "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(3) + ".csv");
    if(!f.is_open())
        throw "error";
    while(!f.eof())
    {
        getline(f,courseID,',');
        cout << "Course ID: " << courseID << " " ;
        getline(f,courseName , ',');
        cout << "Course Name: " << courseName << " " ;
        getline(f,midscore , ',');
        cout << "Midterm Score: " <<midscore << " " ;
        getline(f,finalscore, ',');
        cout << "Final Score: " << finalscore << " " ;
        getline(f,bonus , ',');
        cout << "Bonus: " << bonus << " " ;
        getline(f,overall);
        cout << "GPA: " << overall << " " ;
        cout<<endl;
    }
    f.close();
}
void updateCourse (Students aStudent,Courses courseDelete,fstream &f)
{
    string file="./"+to_string(Schoolyear) + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(courseDelete.sem) + ".csv";
    remove(file.c_str());
    f.open(file);
    Courses *ptem = aStudent.courseStudent ;
    while (ptem!=nullptr)
    {
        f << ptem->courseID << "," << ptem->courseName<< "," << ptem->mark->Midterm<< ","<<ptem->mark->Final<<","<<ptem->mark->Bonus<<","<<ptem->mark->GPA<<endl;
        ptem->next;
    }
    f.close();
}

void removeACourse(Students aStudent,Courses courseDelete,fstream &f)
{
    // xoá trong student // list
    Courses *ptem = aStudent.courseStudent ;
    Courses *pdelete;
    if(ptem->courseID==courseDelete.courseID)
        {
            pdelete=ptem;
            aStudent.courseStudent=aStudent.courseStudent->next;
            delete pdelete;
        }
    else
    {
        while (ptem!=nullptr || ptem->courseID!=courseDelete.courseID)
            ptem->next;
        if (ptem!=nullptr)
            {
                pdelete=ptem;
                ptem=ptem->next;
                delete pdelete;
            };
    };
   
    // xoá trong Course
    BasicStudents *pt = courseDelete.studentID;
    BasicStudents *pdele;
    if (pt==nullptr)
        return;
    if(pt->ID==aStudent.ID)
        {
            pdele=pt;
            courseDelete.studentID=courseDelete.studentID->next;
            delete pdele;
        }
    else
    {
        while (pt!=nullptr && pt->ID!=aStudent.ID)
            pt=pt->next;
        if (pt!=nullptr)
            {
                pdele=pt;
                pt=pt->next;
                delete pdele;
            };
    };
    // gọi hàm doc lai file
        updateCourse(aStudent,courseDelete,f);
};


