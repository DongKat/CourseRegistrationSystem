bool checkSchedule(Students aStudent,Courses courseNew)
{
    BasicCourses *ptem = aStudent.courseStudent ;
    while (ptem!=nullptr)
    {
        if (ptem->sem==courseNew.sem)
        {
            for (int j =0 ; j < 2; j++)
            if((ptem->schedule[j].day == courseNew.schedule[j].day) && (ptem->schedule[j].time== courseNew.schedule[j].time))
                return false;
        }
        ptem=ptem->next;
    }
    return true;
};

void enrollACourse(Students& aStudent,Courses &courseNew,fstream &f)
{
    int k=courseNew.sem;
    int count=-1;
    f.open(Schoolyear+ "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(k) + ".csv", ios::in);
    string ignore_line;
    if(!f.is_open())
        throw "error";
    while(!f.eof())
    {
        getline(f, ignore_line);
        count++;
    }
    f.close();
    f.open(Schoolyear+ "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(k) + ".csv", ios::out|ios::in);
    
    if((checkSchedule(aStudent,courseNew)==true) && courseNew.countStudent<courseNew.maxStudent)
        if(count<5)
        {
            for(int i=0; i<count ; i++)
                getline(f, ignore_line);
            f << courseNew.courseID << "," << courseNew.courseName << ",0,0,0,0," <<courseNew.schedule[0].day<<","<<courseNew.schedule[0].time<<","<<courseNew.schedule[1].day<<","<<courseNew.schedule[1].time<<endl;
            f.close();
            f.open(Schoolyear+ "/Semester/Semester" + to_string(k) + "/" + courseNew.courseID + "Scoreboard.csv", ios::in);
            int count1 = -1;
            if(!f.is_open())
                throw "error";
            while(!f.eof())
            {
                getline(f, ignore_line);
                count1++;
            }
            f.close();
            f.open(Schoolyear+ "/Semester/Semester" + to_string(k) + "/" + courseNew.courseID + "Scoreboard.csv", ios::out|ios::in);
            for(int i=0; i<=count ; i++)
                getline(f, ignore_line);
            f << ++count1 << "," << aStudent.ID << "," << aStudent.firstName << "," << aStudent.lastName << ",0,0,0,0" << endl;
            f.close();
            
            // chèn vào list course student
            BasicCourses *pt=aStudent.courseStudent;
            if(pt==nullptr)
            {
                aStudent.courseStudent=new BasicCourses;
                pt->courseID=courseNew.courseID;
                pt->courseName=courseNew.courseName;
                pt->mark=courseNew.mark;
                for(int i=0; i<2;i++)
                    pt->schedule[i]=courseNew.schedule[i];
                pt->sem=courseNew.sem;
            }
            else
            {
                while(pt->next!= nullptr)
                    pt = pt->next;
                pt->next->courseID=courseNew.courseID;
                pt->next->courseName=courseNew.courseName;
                pt->next->mark=courseNew.mark;
                for(int i=0; i<2;i++)
                    pt->next->schedule[i]=courseNew.schedule[i];
                pt->next->sem=courseNew.sem;
                courseNew.studentID->next=nullptr;
            }
            
            // chèn student vào course
            if (courseNew.countStudent==0)
            {
                courseNew.studentID= new BasicStudents;
                courseNew.studentID->firstName = aStudent.firstName;
                courseNew.studentID->lastName = aStudent.lastName;
                courseNew.studentID->ID = aStudent.ID;
                courseNew.studentID->next=nullptr;
            }
            else
            {
                courseNew.studentID->next = new BasicStudents;
                courseNew.studentID->next->firstName = aStudent.firstName;
                courseNew.studentID->next->lastName = aStudent.lastName;
                courseNew.studentID->next->ID = aStudent.ID;
                courseNew.studentID->next=courseNew.studentID;
            }
            courseNew.countStudent++;
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
    string schedule;
    // in course sem 1
    cout<<"Courses semester 1: "<<endl;
    f.open(Schoolyear+ "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(1) + ".csv");
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
        getline(f,overall, ',');
        cout << "GPA: " << overall << " " ;
        getline(f,schedule, ',');
        cout << "Schedule: " << schedule << " " ;
        getline(f,schedule, ',');
        cout << "Schedule: " << schedule << " " ;
        getline(f,schedule, ',');
        cout << "Schedule: " << schedule << " " ;
        getline(f,schedule);
        cout << "Schedule: " << schedule << " " ;
        cout<<endl;
    }
    f.close();

    // in course sem 2
    cout<<"Courses semester 2: "<<endl;
    f.open(Schoolyear+ "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(2) + ".csv");
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
        getline(f,overall, ',');
        cout << "GPA: " << overall << " " ;
        getline(f,schedule, ',');
        cout << "Schedule: " << schedule << " " ;
        getline(f,schedule, ',');
        cout << "Schedule: " << schedule << " " ;
        getline(f,schedule, ',');
        cout << "Schedule: " << schedule << " " ;
        getline(f,schedule);
        cout << "Schedule: " << schedule << " " ;
        cout<<endl;
    }
    f.close();
    
    // in course sem 3
    cout<<"Courses semester 3: "<<endl;
    f.open(Schoolyear+ "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(3) + ".csv");
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
        getline(f,overall, ',');
        cout << "GPA: " << overall << " " ;
        getline(f,schedule, ',');
        cout << "Schedule: " << schedule << " " ;
        getline(f,schedule, ',');
        cout << "Schedule: " << schedule << " " ;
        getline(f,schedule, ',');
        cout << "Schedule: " << schedule << " " ;
        getline(f,schedule);
        cout << "Schedule: " << schedule << " " ;
        cout<<endl;
    }
    f.close();
}
void updateCourseB4D (Students &aStudent,Courses &courseDelete,fstream &f)
{
    //file student
    string file="./"+Schoolyear + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(courseDelete.sem) + ".csv";
    remove(file.c_str());
    f.open(file,ios::out);
    string temp;
    BasicCourses *ptem = aStudent.courseStudent;
    while (ptem!=nullptr)
    {
        getline(f, temp, ',');
        if (temp == courseDelete.courseID)
        {
            ptem = ptem->next;
        }
        else
        {
            f << ptem->courseID << "," << ptem->courseName<< "," << ptem->mark->Midterm<< ","<<ptem->mark->Final<<","<<ptem->mark->Bonus<<","<<ptem->mark->GPA<<","<<courseDelete.schedule[0].day<<","<<courseDelete.schedule[0].time<<","<<courseDelete.schedule[1].day<<","<<courseDelete.schedule[1].time<<endl;
            ptem=ptem->next;
        }
    }
    f.close();
    
    // file scoreboard
    file="./"+Schoolyear+ "/Semester/Semester" + to_string(courseDelete.sem) + "/" + courseDelete.courseID + "Scoreboard.csv";
    remove(file.c_str());
    f.open(file,ios::out);
    BasicStudents *pCur = courseDelete.studentID;
    int count =1;
    while (pCur!=nullptr)
    {
        getline(f, temp, ',');
        if (temp == aStudent.ID)
        {
            pCur = pCur->next;
        }
        else
        {
            f << count++<< pCur->ID<< "," << pCur->firstName<< "," << pCur->lastName<<","<< aStudent.courseStudent->mark->Midterm<< ","<<aStudent.courseStudent->mark->Final<<","<<aStudent.courseStudent->mark->Bonus<<","<<aStudent.courseStudent->mark->GPA<<endl;
            pCur=pCur->next;
        }
    }
    f.close();
}

void removeACourse(Students *aStudent,Courses *courseDelete,fstream &f)
{
    string ignore_line;
    
    // update file xoá
    updateCourseB4D(*aStudent,*courseDelete,f);
    
    //Xoá dãy studentID cua course
    BasicStudents *pCur = courseDelete->studentID;
    BasicStudents *pdelete;
    while(pCur!=nullptr)
    {
        pdelete=pCur;
        pCur=pCur->next;
        delete pdelete;
    }
    
    // doc lai day studentID tu file
    f.open(Schoolyear+ "/Semester/Semester" + to_string(courseDelete->sem) + "/" + courseDelete->courseID + "Scoreboard.csv", ios::in);
    while(!f.eof())
    {
        pCur= new BasicStudents;
        getline(f,ignore_line,',');
        getline(f,pCur->ID,',');
        getline(f,pCur->firstName,',');
        getline(f,pCur->lastName,',');
        getline(f,ignore_line,',');
        getline(f,ignore_line,',');
        getline(f,ignore_line,',');
        getline(f,ignore_line);
        pCur=pCur->next;
    }
    
    
    //xoa day course cua student
    BasicCourses *temp = aStudent->courseStudent;
    BasicCourses *pdele;
    while(temp!=nullptr)
    {
        pdele=temp;
        temp=temp->next;
        delete pdele;
    }
    
    // doc lai day course cua student tu file
    temp = aStudent->courseStudent;
    f.open(Schoolyear + "/Classes/" + aStudent->className + "/" + aStudent->ID + "/Course Sem" + to_string(courseDelete->sem) + ".csv", ios::in);
    temp->sem=courseDelete->sem;
    while(!f.eof())
    {
        temp= new BasicCourses;
        getline(f,temp->courseID,',');
        getline(f,temp->courseName,',');
        getline(f,ignore_line,',');
        temp->mark->Midterm=stof(ignore_line);
        getline(f,ignore_line,',');
        temp->mark->Final=stof(ignore_line);
        getline(f,ignore_line,',');
        temp->mark->Bonus=stof(ignore_line);
        getline(f,ignore_line);
        temp->mark->GPA=stof(ignore_line);
        for(int i = 2; i < 2; i++)
        {
            temp->schedule[i].day=courseDelete->schedule[i].day;
            temp->schedule[i].time=courseDelete->schedule[i].time;
        }
        temp=temp->next;
    }
    f.close();
};

void viewAllStudentInCourse (Courses
 *course)
{
    int count=1;
    Students *pCur= course->studentID;
    while (pCur !=nullptr)
    {
        cout<<count++<<"ID: "<<pCur->ID<<'\t'<<"Name: " <<pCur->firstName<<" "<<pCur->lastName;
        pCur=pCur->next;
    }
}

void viewAllStudentInClass (Classes *Class)
{
    int count=1;
    Students *pCur= Class->student;
    while (pCur !=nullptr)
    {
        cout<<count++<<"ID: "<<pCur->ID<<'\t'<<"Name: " <<pCur->firstName<<" "<<pCur->lastName;
        pCur=pCur->next;
    }
}
